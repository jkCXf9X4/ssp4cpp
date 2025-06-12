#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "node_base.hpp"
#include "fmu_handler.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{
    // template class to enable constexpression invoke
    class ConnectorNode : public NodeBase
    {
    public:
        common::Logger log = common::Logger("ConnectorNode", common::LogLevel::ext_trace);

        string component_name;
        string connector_name;

        handler::FmuInfo *fmu;
        handler::DataHandler *data_handler;

        uint64_t data_reference;
        uint64_t value_reference;

        size_t data_size;

        ConnectorNode()
        {
        }

        ConnectorNode(std::string component_name,
                      std::string connector_name,
                      handler::FmuInfo *fmu,
                      handler::DataHandler *data_handler,
                      size_t data_size)
        {
            this->component_name = component_name;
            this->connector_name = connector_name;
            update_name();

            this->fmu = fmu;
            this->data_handler = data_handler;

            auto md = this->fmu->model_description;
            value_reference = md->get_variable_by_name(this->connector_name).value_reference;

            this->data_size = data_size;
        }

        virtual ~ConnectorNode()
        {
            log.ext_trace("[{}] Destroying ConnectorNode", __func__);
        }

        // only execute on outputs
        // the data_reference should be passed to the input
        uint64_t create_data_storage()
        {
            // add check if already called, potential memory leak
            data_reference = data_handler->initData(data_size);
            return data_reference;
        }

        void update_name()
        {
            this->name = ConnectorNode::create_name(component_name, connector_name);
        }

        static std::string create_name(string component_name, string connector_name)
        {
            return component_name + "." + connector_name;
        }

        friend ostream &operator<<(ostream &os, const ConnectorNode &obj)
        {
            os << "Connector { \n"
               << "name: " << obj.name << endl
               << " }" << endl;

            return os;
        }

        //
        virtual void read_from_model(uint64_t time) {}

        virtual void write_to_model(uint64_t time) {}
    };

    class BoolConnectorNode : public ConnectorNode
    {
    public:
        using ConnectorNode::ConnectorNode; // forwards the base ctor

        // read value from model and store in data manager
        void read_from_model(uint64_t time) override
        {
            int out_int;
            this->fmu->model->read_boolean(value_reference, out_int);
            bool out = (bool)out_int;
            data_handler->setData(time, data_reference, (void *)&out);
        }

        // retrieve from data manager and input into model
        void write_to_model(uint64_t time) override
        {
            void *data = data_handler->getData(time, data_reference);
            if (data)
            {
                this->fmu->model->write_boolean(value_reference, *(int *)data);
            }
        }
    };

    class IntConnectorNode : public ConnectorNode
    {
    public:
        using ConnectorNode::ConnectorNode; // forwards the base ctor
        // read value from model and store in data manager
        void read_from_model(uint64_t time) override
        {
            int out;
            this->fmu->model->read_integer(value_reference, out);
            data_handler->setData(time, data_reference, (void *)&out);
        }
        void write_to_model(uint64_t time) override
        {
            void *data = data_handler->getData(time, data_reference);
            if (data)
            {
                this->fmu->model->write_integer(value_reference, *(int *)data);
            }
        }
    };

    class DoubleConnectorNode : public ConnectorNode
    {
    public:
        using ConnectorNode::ConnectorNode; // forwards the base ctor
        // read value from model and store in data manager
        void read_from_model(uint64_t time) override
        {
            double out;
            this->fmu->model->read_real(value_reference, out);
            data_handler->setData(time, data_reference, (void *)&out);
        }
        void write_to_model(uint64_t time) override
        {
            void *data = data_handler->getData(time, data_reference);
            if (data)
            {
                this->fmu->model->write_real(value_reference, *(double *)data);
            }
        }
    };

    class StringConnectorNode : public ConnectorNode
    {
    public:
        using ConnectorNode::ConnectorNode; // forwards the base ctor
        // read value from model and store in data manager
        void read_from_model(uint64_t time) override
        {
            char *out_char;
            log.error("[{}] Reading string not implemented", __func__);
            // this->fmu->model->read_string(value_reference, out_char);
            std::string out(out_char);
            data_handler->setData(time, data_reference, (void *)&out);
        }
        void write_to_model(uint64_t time) override
        {
            void *data = data_handler->getData(time, data_reference);
            if (data)
            {
                this->fmu->model->write_string(value_reference, ((std::string *)data)->c_str());
            }
        }
    };

}