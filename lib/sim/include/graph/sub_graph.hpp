#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "invocable.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{

    class SubGraph final : public InvocableNode
    {
        common::Logger log = common::Logger("SubGraph", common::LogLevel::debug);

        uint64_t delay = 0;
        uint64_t start_time = 0;
        uint64_t end_time = 0;
        uint64_t delayed_time = 0;

        SubGraph()
        {
        }

        ~SubGraph()
        {
            log.ext_trace("[{}] Destroying SubGraph", __func__);
        }

        friend std::ostream &operator<<(std::ostream &os, const SubGraph &obj)
        {
            os << "SubGraph { \n"
               << "delay: " << obj.delay << std::endl
               << " }" << std::endl;

            return os;
        }

        void init() override
        {
        }

        uint64_t invoke(StepData step_data) override final
        {
            log.ext_trace("[{}] stepdata: {}", __func__, step_data.to_string());

            return step_data.end_time;
        }
    };
}