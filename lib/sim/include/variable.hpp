#pragma once

#include "common_node.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "fmu.hpp"
#include "data_manager.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>
#include <functional>
#include <tuple>

namespace ssp4cpp::sim
{

    class VariableBase
    {
        common::Logger log = common::Logger("sim::VariableBase", common::LogLevel::ext_trace);

    public:
        std::string name;
        uint64_t value_reference;
        uint64_t data_reference;
        sim::data::DataManager *data_manager;
        fmi4cpp::fmi2::cs_slave *home_model;

        VariableBase() = default;
        VariableBase(std::string name,
                     uint64_t value_reference,
                     sim::data::DataManager *dm,
                     fmi4cpp::fmi2::cs_slave *home_model)
            : name(name), data_manager(dm), home_model(home_model)
        {
            this->value_reference = value_reference;
        }
        virtual ~VariableBase() = default;
        virtual void add_to_data_manager() = 0;
        virtual void set_to_model(fmi4cpp::fmi2::cs_slave &model, uint64_t time) = 0;
        virtual void update_from_model(uint64_t time) = 0;
    };

    class BoolVariable : public VariableBase
    {
    public:
        using VariableBase::VariableBase;
        void add_to_data_manager() override
        {
            data_reference = data_manager->initData(sizeof(bool));
        }
        void set_to_model(fmi4cpp::fmi2::cs_slave &model, uint64_t time) override
        {
            void *data = data_manager->getData(time, data_reference);
            model.write_boolean(value_reference, *(int *)data);
        }
        void update_from_model(uint64_t time)
        {
            int out_int;
            home_model->read_boolean(value_reference, out_int);
            bool out = (bool)out_int;
            data_manager->setData(time, data_reference, (void *)&out);
        }
    };

    class IntVariable : public VariableBase
    {
    public:
        using VariableBase::VariableBase;
        void add_to_data_manager() override
        {
            data_reference = data_manager->initData(sizeof(int));
        }
        void set_to_model(fmi4cpp::fmi2::cs_slave &model, uint64_t time) override
        {
            void *data = data_manager->getData(time, data_reference);
            model.write_integer(value_reference, *(int *)data);
        }
        void update_from_model(uint64_t time)
        {
            int out;
            home_model->read_integer(value_reference, out);
            data_manager->setData(time, data_reference, (void *)&out);
        }
    };

    class DoubleVariable : public VariableBase
    {
    public:
        using VariableBase::VariableBase;
        void add_to_data_manager() override
        {
            data_reference = data_manager->initData(sizeof(double));
        }
        void set_to_model(fmi4cpp::fmi2::cs_slave &model, uint64_t time) override
        {
            void *data = data_manager->getData(time, data_reference);
            model.write_real(value_reference, *(double *)data);
        }
        void update_from_model(uint64_t time)
        {
            double out;
            home_model->read_real(value_reference, out);
            data_manager->setData(time, data_reference, (void *)&out);
        }
    };

    class StringVariable : public VariableBase
    {
    public:
        using VariableBase::VariableBase;
        void add_to_data_manager() override
        {
            data_reference = data_manager->initData(sizeof(std::string));
        }
        void set_to_model(fmi4cpp::fmi2::cs_slave &model, uint64_t time) override
        {
            void *data = data_manager->getData(time, data_reference);
            model.write_string(value_reference, ((std::string *)data)->c_str());
        }
        void update_from_model(uint64_t time)
        {
            char *out_char;
            home_model->read_string(value_reference, out_char);
            std::string out(out_char);
            data_manager->setData(time, data_reference, (void *)&out);
        }
    };

    // Helper: create_variable with explicit type and context
    inline std::unique_ptr<VariableBase> create_variable(
        const std::string &name,
        fmi4cpp::fmi2::cs_model_description &md,
        sim::data::DataManager *dm,
        fmi4cpp::fmi2::cs_slave *home_model)
    {
        auto variable = md.get_variable_by_name(name);
        auto vr = variable.value_reference;
        if (variable.is_boolean())
        {
            return std::make_unique<BoolVariable>(name, vr, dm, home_model);
        }
        else if (variable.is_integer() || variable.is_enumeration())
        {
            return std::make_unique<IntVariable>(name, vr, dm, home_model);
        }
        else if (variable.is_real())
        {
            return std::make_unique<DoubleVariable>(name, vr, dm, home_model);
        }
        else if (variable.is_string())
        {
            return std::make_unique<StringVariable>(name, vr, dm, home_model);
        }
        else
        {

            throw runtime_error("Unknown type");
        }
    }

}