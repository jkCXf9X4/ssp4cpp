

#pragma once

#include "SSP1_SystemStructureParameterValues.hpp"
#include "SSP1_SystemStructureParameterMapping.hpp"
#include "FMI2_modelDescription.hpp"

#include "FMI2_Enums_Ext.hpp"

#include <memory>
#include <cstring>

namespace ssp4cpp::ssp1::ext::ssv
{
    using namespace ssp4cpp::ssp1::ssv;
    using namespace ssp4cpp::ssp1::ssm;

    using DataType = ssp4cpp::fmi2::ext::enums::DataType;

    struct Parameter
    {
        std::string name;
        DataType type;
        size_t size;
        std::unique_ptr<std::byte[]>value;

        Parameter(std::string name, DataType type)
        {
            this->name = name;
            this->type = type;
            this->size = fmi2::ext::enums::get_data_type_size(type);
            this->value = std::make_unique<std::byte[]>(this->size);
        }

        Parameter(const Parameter &other)
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

        Parameter(Parameter &&other) noexcept = default;

        Parameter &operator=(const Parameter &other)  = default;
        Parameter &operator=(Parameter &&other) noexcept = default;

        void store_value(void* value)
        {
            if (this->type == DataType::string)
            {
                log.ext_trace("[{}] Storing value {}", __func__, *(string*)value); 
                auto s = (string*)this->value.get();
                *s = *(string*)value;
                log.ext_trace("[{}] Value stored {}", __func__, *(string*)this->value.get()); 
                return;
            }
            memcpy((void*)this->value.get(), value, this->size);
        }
    };

    struct Mapping
    {
        std::string source;
        std::string target;

        Mapping(std::string source, std::string target)
        {
            this->source = source;
            this->target = target;
        }
    };

    struct Bindings
    {
        std::unique_ptr<ssp1::ssv::ParameterSet> ssv;
        std::unique_ptr<ssp1::ssm::ParameterMapping> ssm;
        std::vector<Parameter> parameters;
        std::vector<Mapping> mappings;
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
    

}
