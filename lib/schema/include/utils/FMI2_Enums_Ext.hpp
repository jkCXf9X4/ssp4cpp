
#pragma once

#include "common_log.hpp"

#include "FMI2_Enums.hpp"

#include <string>

namespace ssp4cpp::fmi2::ext
{

    namespace enums
    {
        inline auto log = common::Logger("fmi2.ext.enums", common::LogLevel::debug);

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
                return sizeof(std::string);
            case DataType::unknown:
                return 0;
            }
            // If the enum gains a new value and the switch isn’t updated,
            // this keeps the compiler happy in -Wall/-Wswitch-enums builds.
            throw std::invalid_argument("Unknown DataType");
        }
    }

}
