
#include "common_time.hpp"

/**
 * @brief Time related utility constants.
 */
namespace ssp4cpp::common::time
{

        ScopeTimer::ScopeTimer(std::string label)
            : label_(label), start_(clock::now()) {}

        ScopeTimer::~ScopeTimer()
        {
            const auto dur = std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - start_);
            // log: "<func> <label> took X µs"
            log.info("[ScopeTimer] {} took {} µs", label_, dur.count());
        }
}
