#pragma once

#include "common_log.hpp"

#include <chrono>
#include <string>

/**
 * @brief Time related utility constants.
 */
namespace ssp4cpp::common::time
{
    uint64_t constexpr milliseconds_per_second = 1000;
    uint64_t constexpr microseconds_per_second = 1000000;
    uint64_t constexpr nanoseconds_per_second = 1000000000;

    uint64_t constexpr nanoseconds_per_millisecond = 1000000;
    uint64_t constexpr nanoseconds_per_microsecond = 1000;

    uint64_t constexpr seconds_per_hour = 3600;
    uint64_t constexpr hours_per_day = 24;

    class ScopeTimer
    {
    public:
        using clock = std::chrono::steady_clock;

        common::Logger log = common::Logger("ScopeTimer", common::LogLevel::debug);

        ScopeTimer(std::string label);

        ~ScopeTimer();

    private:
        std::string label_;
        clock::time_point start_;
    };
}
