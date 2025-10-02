#pragma once

#include "common_log.hpp"
#include "common_map.hpp"
#include "common_vector.hpp"

#include "invocable.hpp"
#include "jacobi.hpp"
#include "seidel.hpp"

#include "config.hpp"

#include <vector>
#include <algorithm>
#include <map>

namespace ssp4cpp::sim::graph
{

    class Graph final : public Invocable
    {
    public:
        common::Logger log = common::Logger("Graph", common::LogLevel::info);

        std::map<std::string, std::unique_ptr<AsyncNode>> models;
        std::vector<AsyncNode *> nodes;

        std::string executor_method;
        std::unique_ptr<ExecutionBase> executor;

        Graph() = default;

        Graph(std::map<std::string, std::unique_ptr<AsyncNode>> models_)
            : models(std::move(models_))
        {
            auto m = common::map_ns::map_unique_to_ref(models);
            nodes = common::map_ns::map_to_value_vector_copy(m);

            executor_method = utils::Config::getOr<std::string>("simulation.executor", "jacobi");
        }

        virtual void print(std::ostream &os) const
        {
            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(nodes));

            os << "Simulation Graph DOT:\n"
               << common::graph::Node::to_dot(nodes) << "\n"
               << common::graph::ssc_to_string(strong_system_graph) << "\n";

            os << "Models:\n";
            for (auto &[name, model] : models)
            {
                os << "Model: " << name << "\n";
            }
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

        // hot path
        uint64_t invoke(StepData step_data) override final
        {
#ifdef _LOG_
            log.trace("[{}] Invoking Graph, full step: {}", __func__, step_data.to_string());
#endif

            auto t = step_data.start_time;
            while (t < step_data.end_time)
            {
                auto s = StepData(t, t + step_data.timestep, step_data.timestep);
#ifdef _LOG_
                log.ext_trace("[{}] Graph executing step: {}", __func__, s.to_string());
#endif
                executor->invoke(s);

                t += step_data.timestep;
            }
            return t;
        }
    };

}