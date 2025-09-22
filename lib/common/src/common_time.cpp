
#include "common_time.hpp"

/**
 * @brief Time related utility constants.
 */
namespace ssp4cpp::common::time
{

    ScopeTimer::ScopeTimer(std::string label)
        : label_(label), start_(clock::now()) {}

    ScopeTimer::ScopeTimer(std::string label, uint64_t *result_callback_) : ScopeTimer(label)
    {
        result_callback_ns = result_callback_;
    }

    ScopeTimer::~ScopeTimer()
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
}
