#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "model.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{


    class SubGraph : public common::graph::Node
    {
         common::Logger log = common::Logger("Model", common::LogLevel::debug);

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

        friend ostream &operator<<(ostream &os, const SubGraph &obj)
        {
            os << "SubGraph { \n"
               << "delay: " << obj.delay << endl
               << " }" << endl;

            return os;
        }

                /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }

        uint64_t invoke(uint64_t start_time, uint64_t end_time, uint64_t timestep)
        {
            return end_time;
        }

    };
}