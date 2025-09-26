#pragma once

#include "FMI2_Enums.hpp"

#include "handler/fmi4c_adapter.hpp"

#include <cstddef>
#include <string>
#include <stdexcept>

namespace ssp4cpp::sim::utils
{
    using DataType = ssp4cpp::fmi2::md::Type;

    inline constexpr void read_from_model_(DataType t,
                                           handler::CoSimulationModel &model,
                                           uint64_t value_reference,
                                           void *out)
    {
        switch (t)
        {
        case DataType::real:
        {
            double value = 0.0;
            if (!model.read_real(value_reference, value))
            {
                throw std::runtime_error("Failed to read real value from FMU");
            }
            *(double *)out = value;
            return;
        }
        case DataType::boolean:
        {
            int value = 0;
            if (!model.read_boolean(value_reference, value))
            {
                throw std::runtime_error("Failed to read boolean value from FMU");
            }
            *(int *)out = value;
            return;
        }
        case DataType::integer:
        case DataType::enumeration:
        {
            int value = 0;
            if (!model.read_integer(value_reference, value))
            {
                throw std::runtime_error("Failed to read integer value from FMU");
            }
            *(int *)out = value;
            return;
        }
        case DataType::string:
            throw std::invalid_argument("String not supported");
        //     model.read_string(value_reference, *(const char *)out);
            return;
        case DataType::unknown:
            return;
        }
        throw std::invalid_argument("Unknown DataType");
    }

    inline constexpr void write_to_model_(DataType t,
                                          handler::CoSimulationModel &model,
                                          uint64_t &value_reference,
                                          void *data)
    {
        switch (t)
        {
        case DataType::real:
        {
            auto value = *(double *)data;
            if (!model.write_real(value_reference, value))
            {
                throw std::runtime_error("Failed to write real value to FMU");
            }
            return;
        }
        case DataType::boolean:
        {
            auto value = *(int *)data;
            if (!model.write_boolean(value_reference, value))
            {
                throw std::runtime_error("Failed to write boolean value to FMU");
            }
            return;
        }
        case DataType::integer:
        case DataType::enumeration:
        {
            auto value = *(int *)data;
            if (!model.write_integer(value_reference, value))
            {
                throw std::runtime_error("Failed to write integer value to FMU");
            }
            return;
        }
        case DataType::string:
        {
            auto s = (std::string *)data;
            if (!model.write_string(value_reference, *s))
            {
                throw std::runtime_error("Failed to write string value to FMU");
            }
            return;
        }
        case DataType::unknown:
            return;
        }
        throw std::invalid_argument("Unknown DataType");
    }


}
