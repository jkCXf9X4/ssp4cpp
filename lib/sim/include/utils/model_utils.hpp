#pragma once

#include "data_type.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::utils
{

    inline constexpr void read_from_model_(DataType t,
                                          fmi4cpp::fmi2::cs_slave &model,
                                          uint64_t value_reference,
                                          void *out)
    {
        switch (t)
        {
        case DataType::real:
            model.read_real(value_reference, *(double *)out);
            return;
        case DataType::boolean:
            model.read_boolean(value_reference, *(int *)out);
            return;
        case DataType::integer:
        case DataType::enumeration:
            model.read_integer(value_reference, *(int *)out);
            return;
        // case DataType::string:
        //     model.read_string(value_reference, *(const char *)out);
        //     return;
        case DataType::unknown:
            return;
        }
        throw std::invalid_argument("Unknown DataType");
    }

    inline constexpr void write_to_model_(DataType t,
                                         fmi4cpp::fmi2::cs_slave &model,
                                         uint64_t &value_reference,
                                         void *data)
    {
        switch (t)
        {
        case DataType::real:
            model.write_real(value_reference, *(int *)data);
            return;
        case DataType::boolean:
            model.write_boolean(value_reference, *(int *)data);
            return;
        case DataType::integer:
        case DataType::enumeration:
            model.write_integer(value_reference, *(int *)data);
            return;
        // case DataType::string:
        //     model.write_string(value_reference, *(int *)data);
        //     return;
        case DataType::unknown:
            return;
        }
        throw std::invalid_argument("Unknown DataType");
    }

        DataType get_variable_type(fmi4cpp::fmi2::scalar_variable var)
    {
        if (var.is_boolean())
        {
            return DataType::boolean;
        }
        else if (var.is_enumeration())
        {
            return DataType::enumeration;
        }
        else if (var.is_integer())
        {
            return DataType::integer;
        }
        else if (var.is_real())
        {
            return DataType::real;
        }
        else if (var.is_string())
        {
            return DataType::string;
        }
        else
        {
            throw runtime_error("Unknown type");
        }
    }
}