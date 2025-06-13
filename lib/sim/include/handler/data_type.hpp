#pragma once

#include <cstddef>
#include <string>
#include <stdexcept>

namespace ssp4cpp::sim::handler
{
    using namespace std;

    enum class DataType
    {
        BOOL,
        INT,
        REAL,
        STRING,
        ENUM,
        UNKNOWN
    };

    /**
     * @brief  Return the in-memory size (in bytes) of a single value
     *         represented by the given DataType.
     */
    constexpr std::size_t get_data_type_size(DataType t)
    {
        switch (t)
        {
        case DataType::BOOL:
            return sizeof(bool); // typically 1
        case DataType::INT:
            return sizeof(int); // typically 4
        case DataType::REAL:
            return sizeof(double); // typically 8
        case DataType::ENUM:
            return sizeof(int); // stored like an int
        case DataType::STRING:
            return sizeof(std::string);
        case DataType::UNKNOWN:
            return 0;
        }
        // If the enum gains a new value and the switch isn’t updated,
        // this keeps the compiler happy in -Wall/-Wswitch-enums builds.
        throw std::invalid_argument("Unknown DataType");
    }

}