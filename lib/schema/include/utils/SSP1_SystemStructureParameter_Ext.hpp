

#pragma once

#include "common_log.hpp"

#include "FMI2_modelDescription.hpp"
#include "SSP1_SystemStructureDescription.hpp"

#include "SSP1_SystemStructureParameterValues.hpp"
#include "SSP1_SystemStructureParameterMapping.hpp"

#include "FMI2_Enums_Ext.hpp"

#include <memory>
#include <cstring>
#include <filesystem>

namespace ssp4cpp::ssp1::ext::ssv
{
    inline auto log = common::Logger("ssp4cpp.ssp1.ext.ssv", common::LogLevel::info);

    using namespace ssp4cpp::ssp1::ssv;
    using namespace ssp4cpp::ssp1::ssm;

    using DataType = ssp4cpp::fmi2::ext::enums::DataType;

    struct StartValue
    {
        std::string name;
        std::vector<std::string> mappings; // name + mappings
        DataType type;
        size_t size;
        std::unique_ptr<std::byte[]> value;

        StartValue(std::string name, DataType type)
        {
            this->name = name;
            this->type = type;
            this->size = fmi2::ext::enums::get_data_type_size(type);
            this->value = std::make_unique<std::byte[]>(this->size);
            mappings.push_back(name);
        }

        // copystructor
        StartValue(const StartValue &other)
        {
            name = other.name;
            type = other.type;
            size = other.size;
            if (other.value)
            {
                value = std::make_unique<std::byte[]>(size);
                std::memcpy(value.get(), other.value.get(), size);
            }
        }

        // Copy assignment operator
        StartValue &operator=(const StartValue &other)
        {
            if (this == &other) // self-assignment check
                return *this;

            name = other.name;
            mappings = other.mappings;
            type = other.type;
            size = other.size;

            if (other.value)
            {
                value = std::make_unique<std::byte[]>(size);
                std::copy(other.value.get(), other.value.get() + size, value.get());
            }
            else
            {
                value.reset();
            }

            return *this;
        }

        StartValue(StartValue &&other) noexcept = default;

        // StartValue &operator=(const StartValue &other) = default;
        // StartValue &operator=(StartValue &&other) noexcept = default;

        std::unique_ptr<std::byte[]> get_value()
        {
            auto v = std::make_unique<std::byte[]>(size);
            std::memcpy(v.get(), value.get(), size);
            return std::move(v);
        }

        void store_value(void *value)
        {
            if (this->type == DataType::string)
            {
                log.ext_trace("[{}] Storing value {}", __func__, *(string *)value);
                
                auto s = (string *)this->value.get();
                *s = *(string *)value;
            }
            else
            {
                memcpy((void *)this->value.get(), value, this->size);
            }
        }
    };

    struct ParameterBindings
    {
        std::unique_ptr<ssp1::ssv::ParameterSet> ssv;
        std::unique_ptr<ssp1::ssm::ParameterMapping> ssm;
    };

    inline DataType get_parameter_type(TParameter &par)
    {
        if (par.Boolean.has_value())
        {
            return DataType::boolean;
        }
        else if (par.Enumeration.has_value())
        {
            return DataType::enumeration;
        }
        else if (par.Integer.has_value())
        {
            return DataType::integer;
        }
        else if (par.Real.has_value())
        {
            return DataType::real;
        }
        else if (par.String.has_value())
        {
            return DataType::string;
        }
        else
        {
            throw runtime_error("Unknown type");
        }
    }

    inline void *get_parameter_value(TParameter &par)
    {
        if (par.Boolean.has_value())
        {
            return &par.Boolean.value().value;
        }
        else if (par.Enumeration.has_value())
        {
            return &par.Enumeration.value().value;
        }
        else if (par.Integer.has_value())
        {
            return &par.Integer.value().value;
        }
        else if (par.Real.has_value())
        {
            return &par.Real.value().value;
        }
        else if (par.String.has_value())
        {
            return &par.String.value().value;
        }
        return nullptr;
    }

    std::map<std::string, StartValue> get_start_value_mappings(std::filesystem::path &dir, ssp1::ssd::SystemStructureDescription &ssd);

}
