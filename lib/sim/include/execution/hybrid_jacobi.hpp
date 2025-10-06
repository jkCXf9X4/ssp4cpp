#pragma once

#include "common_log.hpp"

#include "execution.hpp"

#include "task_thread_pool.hpp"
#include "task_thread_pool2.hpp"

#include "config.hpp"

#include <assert.h>
#include <execution>

namespace ssp4cpp::sim::graph
{
    // Jacobi w direct feedthrough

    // circle over all direct feedthrough until they are stable
    // then run the models in parallel 

    class HybridJacobi final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("HybridJacobi", common::LogLevel::info);


        HybridJacobi(std::vector<AsyncNode *> nodes) : ExecutionBase(std::move(nodes))
        {
        }

        virtual void print(std::ostream &os) const
        {
            os << "HybridJacobi:\n{}\n";
        }

        void init() override
        {
        }

        // hot path
        uint64_t invoke(StepData step_data, const bool only_feedthrough = false) override final
        {
        }
    };
}
