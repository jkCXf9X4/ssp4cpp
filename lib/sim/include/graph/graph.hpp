#pragma once

#include "common_log.hpp"
#include "common_map.hpp"
#include "common_vector.hpp"

#include "invocable.hpp"
#include "execution.hpp"
#include "config.hpp"

#include <vector>
#include <algorithm>
#include <map>

namespace ssp4cpp::sim::graph
{

    class Graph final : public InvocableNode
    {
    public:
        common::Logger log = common::Logger("Graph", common::LogLevel::debug);

        std::map<std::string, std::unique_ptr<InvocableNode>> models;
        std::vector<InvocableNode *> nodes;

        std::string executor_method;
        std::unique_ptr<ExecutionBase> executor;

        Graph() = default;

        Graph(std::map<std::string, std::unique_ptr<InvocableNode>> models_)
            : models(std::move(models_))
        {
            auto m = common::map_ns::map_unique_to_ref(models);
            nodes = common::map_ns::map_to_value_vector_copy(m);

            executor_method = utils::Config::getOr<std::string>("simulation.executor", "jacobi");
        }

        friend std::ostream &operator<<(std::ostream &os, const Graph &obj)
        {
            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(obj.nodes));

            os << "Simulation Graph DOT:\n"
               << common::graph::Node::to_dot(obj.nodes) << std::endl
               << common::graph::ssc_to_string(strong_system_graph) << std::endl;

            os << "Models:" << std::endl;
            for (auto &[name, model] : obj.models)
            {
                os << "Model: " << name << std::endl;
            }
            return os;
        }

        void init()
        {
            log.trace("[{}] Initializing Graph", __func__);

            if (executor_method == "jacobi")
            {
                log.info("[{}] Running jacobi", __func__);
                executor = make_unique<Jacobi>(nodes);
            }
            else if (executor_method == "seidel")
            {
                log.info("[{}] Running seidel", __func__);
                executor = make_unique<Seidel>(nodes);
            }

            log.trace("[{}] - Initializing models ", __func__);

            for (auto &[_, model] : this->models)
            {
                log.ext_trace("[{}] -- Initializing model: {} ", __func__, model->name);
                model->init();
            }
            log.ext_trace("[{}] - Model init completed", __func__);
        }

        uint64_t invoke(StepData step_data) override final
        {
            log.ext_trace("[{}] Graph - stepdata: {}", __func__, step_data.to_string());

            auto t = step_data.start_time;
            while (t < step_data.end_time)
            {
                log.ext_trace("[{}] NEW TIME {}", __func__, t);
                executor->invoke(StepData(t, t + step_data.timestep, step_data.timestep));

                t += step_data.timestep;
            }
            return t;
        }
    };

}