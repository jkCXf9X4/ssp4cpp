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
            if (!model.read_real(value_reference, *(double *)out))
            {
                throw std::runtime_error("Failed to read real value from FMU");
            }
            return;
        }
        case DataType::boolean:
        {
            if (!model.read_boolean(value_reference, *(int *)out))
            {
                throw std::runtime_error("Failed to read boolean value from FMU");
            }
            return;
        }
        case DataType::integer:
        case DataType::enumeration:
        {
            if (!model.read_integer(value_reference, *(int *)out))
            {
                throw std::runtime_error("Failed to read integer value from FMU");
            }
            return;
        }
        case DataType::string:
        {
            if (!model.read_string(value_reference, *(std::string *)out))
            {
                throw std::runtime_error("Failed to read string value from FMU");
            }
            return;
        }
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
            if (!model.write_real(value_reference, *(double *)data))
            {
                throw std::runtime_error("Failed to write real value to FMU");
            }
            return;
        }
        case DataType::boolean:
        {
            if (!model.write_boolean(value_reference, *(int *)data))
            {
                throw std::runtime_error("Failed to write boolean value to FMU");
            }
            return;
        }
        case DataType::integer:
        case DataType::enumeration:
        {
            if (!model.write_integer(value_reference, *(int *)data))
            {
                throw std::runtime_error("Failed to write integer value to FMU");
            }
            return;
        }
        case DataType::string:
        {
            if (!model.write_string(value_reference, *(std::string *)data))
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
