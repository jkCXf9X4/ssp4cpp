#pragma once

#include "data_type.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::utils
{

    inline constexpr void read_from_model_(handler::DataType t,
                                          fmi4cpp::fmi2::cs_slave &model,
                                          uint64_t value_reference,
                                          void *out)
    {
        switch (t)
        {
        case handler::DataType::real:
            model.read_real(value_reference, *(double *)out);
            return;
        case handler::DataType::boolean:
            model.read_boolean(value_reference, *(int *)out);
            return;
        case handler::DataType::integer:
        case handler::DataType::enumeration:
            model.read_integer(value_reference, *(int *)out);
            return;
        // case handler::DataType::string:
        //     model.read_string(value_reference, *(const char *)out);
        //     return;
        case handler::DataType::unknown:
            return;
        }
        throw std::invalid_argument("Unknown DataType");
    }

    inline constexpr void write_to_model_(handler::DataType t,
                                         fmi4cpp::fmi2::cs_slave &model,
                                         uint64_t &value_reference,
                                         void *data)
    {
        switch (t)
        {
        case handler::DataType::real:
            model.write_real(value_reference, *(int *)data);
            return;
        case handler::DataType::boolean:
            model.write_boolean(value_reference, *(int *)data);
            return;
        case handler::DataType::integer:
        case handler::DataType::enumeration:
            model.write_integer(value_reference, *(int *)data);
            return;
        // case handler::DataType::string:
        //     model.write_string(value_reference, *(int *)data);
        //     return;
        case handler::DataType::unknown:
            return;
        }
        throw std::invalid_argument("Unknown DataType");
    }
}