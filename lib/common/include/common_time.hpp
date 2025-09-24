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

        ScopeTimer(std::string label) : label_(label), start_(clock::now()) {}

        ScopeTimer(std::string label, uint64_t *result_callback) : ScopeTimer(label)
        {
            result_callback_ns = result_callback;
        }

        ~ScopeTimer()
        {
            const auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - start_);

            // log: "<func> <label> took X µs"
            if (result_callback_ns == nullptr)
            {
                log.info("[ScopeTimer] {} took {}ns", label_, (double)dur.count() / ssp4cpp::common::time::nanoseconds_per_second);
            }
            else
            {
                *result_callback_ns = dur.count();
            }
        }

    private:
        std::string label_;
        clock::time_point start_;
        uint64_t *result_callback_ns = nullptr;
    };

    class Timer
    {
    public:
        using clock = std::chrono::steady_clock;

        // common::Logger log = common::Logger("Timer", common::LogLevel::debug);

        Timer() : start_(clock::now()) {}

        uint64_t stop()
        {
            const auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - start_);
            return dur.count();
        }

        ~Timer()
        {
        }

    private:
        clock::time_point start_;
    };
}
