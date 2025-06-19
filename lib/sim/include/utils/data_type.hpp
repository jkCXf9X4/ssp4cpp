#pragma once

#include "FMI2_Enums.hpp"

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
    constexpr std::size_t get_data_type_size(DataType t)
    {
        switch (t)
        {
        case DataType::boolean:
            return sizeof(bool); // typically 1
        case DataType::integer:
            return sizeof(int); // typically 4
        case DataType::real:
            return sizeof(double); // typically 8
        case DataType::enumeration:
            return sizeof(int); // stored like an int
        case DataType::string:
            return 250; // max size of string
        case DataType::unknown:
            return 0;
        }
        // If the enum gains a new value and the switch isn’t updated,
        // this keeps the compiler happy in -Wall/-Wswitch-enums builds.
        throw std::invalid_argument("Unknown DataType");
    }

}