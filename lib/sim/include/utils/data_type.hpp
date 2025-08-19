#pragma once

#include "FMI2_Enums.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <vector>
#include <cstddef>
#include <string>
#include <stdexcept>

namespace ssp4cpp::sim::utils
{
    using namespace std;

    using DataType = ssp4cpp::fmi2::md::Type;

    /**
     * @brief  Return the in-memory size (in bytes) of a single value
     *         represented by the given DataType.
     */
    inline constexpr std::size_t get_data_type_size(DataType t)
    {
        switch (t)
        {
        case DataType::boolean:
            return sizeof(bool); // typically 1
        case DataType::integer:
        case DataType::enumeration:
            return sizeof(int); // typically 4
        case DataType::real:
            return sizeof(double); // typically 8
        case DataType::string:
            return 250; // max size of string
        case DataType::unknown:
            return 0;
        }
        // If the enum gains a new value and the switch isn’t updated,
        // this keeps the compiler happy in -Wall/-Wswitch-enums builds.
        throw std::invalid_argument("Unknown DataType");
    }

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

    inline DataType get_variable_type(fmi4cpp::fmi2::scalar_variable var)
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