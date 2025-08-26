#pragma once

#include "common_log.hpp"
#include "common_map.hpp"
#include "common_vector.hpp"

#include "model.hpp"
#include "execution.hpp"

#include <vector>
#include <algorithm>
#include <map>

namespace ssp4cpp::sim::graph
{

    class Graph
    {
    public:
        common::Logger log = common::Logger("Graph", common::LogLevel::debug);

        std::map<string, unique_ptr<Model>> models;
        std::vector<Model *> nodes;
        
        std::unique_ptr<ExecutionBase> executor;

        Graph() = default;

        Graph(std::map<string, unique_ptr<Model>> models_)
            : models(std::move(models_))
        {
            auto m = map_ns::map_unique_to_ref(models);
            nodes = common::map_ns::map_to_value_vector_copy(m);

            executor = make_unique<Jacobi>(nodes);
        }

        friend std::ostream &operator<<(std::ostream &os, const Graph &obj)
        {
            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(obj.nodes));
            
            os << "Simulation Graph DOT:\n" 
            << common::graph::Node::to_dot(obj.nodes) << std::endl
            << common::graph::ssc_to_string(strong_system_graph) << std::endl;

            os << "Storage areas:" << std::endl;
            for (auto &[name, model] : obj.models)
            {
                os << "Model: " << name << std::endl
                << " Input: " << *model->input_area << std:: endl
                << " Output: " << *model->output_area << std::endl;
            }
            return os;
        }

        /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }

        uint64_t invoke(uint64_t start_time, uint64_t end_time, uint64_t timestep)
        {
            auto t = start_time;
            while (t < end_time)
            {
                t += timestep;

                log.ext_trace("[{}] NEW TIME {}", __func__, t);
                executor->invoke(t);
            }
            return t;

        }
    };

}