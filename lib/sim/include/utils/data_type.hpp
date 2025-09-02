#pragma once

#include "FMI2_Enums.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <vector>
#include <cstddef>
#include <string>
#include <stdexcept>

namespace ssp4cpp::sim::utils
{
    using DataType = ssp4cpp::fmi2::md::Type;

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


}