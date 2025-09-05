

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
        std::unique_ptr<std::byte[]> value; // owning, raw byte buffer

        Parameter(std::string name_, DataType type_)
            : name(std::move(name_)),
              type(type_),
              size(fmi2::ext::enums::get_data_type_size(type_)),
              value(size ? std::make_unique<std::byte[]>(size) : nullptr) // value-initialized (zeros)
        {
        }

        // Deep-copy constructor
        Parameter(const Parameter &other)
            : name(other.name),
              type(other.type),
              size(other.size),
              value(other.size ? std::make_unique<std::byte[]>(other.size) : nullptr)
        {
            if (other.value)
            {
                std::memcpy(value.get(), other.value.get(), other.size);
            }
        }

        // // Copy assignment (copy-and-swap for strong exception safety)
        // Parameter &operator=(Parameter other) noexcept
        // {
        //     swap(*this, other);
        //     return *this;
        // }

        // Moves can be defaulted (unique_ptr is movable)
        Parameter(Parameter &&) noexcept = default;
        Parameter &operator=(Parameter &&) noexcept = default;

        // Store from untyped memory (size must match)
        void store_value(const void *value)
        {
            if (this->type == DataType::string)
            {
                log.warning("[{}] Values of string not supported", __func__);
                return;
            }
            if (!this->value || !value)
                return;
            std::memcpy(this->value.get(), value, this->size);
        }

        friend void swap(Parameter &a, Parameter &b) noexcept
        {
            using std::swap;
            swap(a.name, b.name);
            swap(a.type, b.type);
            swap(a.size, b.size);
            swap(a.value, b.value);
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
