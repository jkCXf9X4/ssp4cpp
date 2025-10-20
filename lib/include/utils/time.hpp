#pragma once

#include "utils/log.hpp"

#include <chrono>
#include <string>

/**
 * @brief Time related utility constants.
 */
namespace ssp4cpp::utils::time
{
    uint64_t constexpr milliseconds_per_second = 1000;
    uint64_t constexpr microseconds_per_second = 1000000;
    uint64_t constexpr nanoseconds_per_second = 1000000000;

    uint64_t constexpr nanoseconds_per_millisecond = 1000000;
    uint64_t constexpr nanoseconds_per_microsecond = 1000;

    uint64_t constexpr seconds_per_hour = 3600;
    uint64_t constexpr hours_per_day = 24;

    inline double ns_to_s(uint64_t t)
    {
        return static_cast<double>(t) / utils::time::nanoseconds_per_second;
    }

    inline uint64_t s_to_ns(double t)
    {
        return static_cast<uint64_t>(t * utils::time::nanoseconds_per_second);
    }

}
