#pragma once

#include "common_log.hpp"

#include "invocable.hpp"
#include "async_node.hpp"
#include "task_thread_pool.hpp"
#include "task_thread_pool2.hpp"

#include "config.hpp"

#include <assert.h>
#include <execution>

namespace ssp4cpp::sim::graph
{

    class ExecutionBase : public Invocable
    {
    public:
        common::Logger log = common::Logger("ExecutionBase", common::LogLevel::info);
        std::vector<AsyncNode *> nodes;

        bool parallelize;
        std::unique_ptr<SharedState> shared_state;

        ExecutionBase(std::vector<AsyncNode *> nodes) : nodes(std::move(nodes))
        {
            log.trace("[{}] Setting up shared state", __func__);
            shared_state = std::make_unique<SharedState>();

            for (int i = 0; i < this->nodes.size(); i++)
            {
                this->nodes[i]->set_shared_state(i, shared_state.get());
            }
        }
    };

    class Seidel final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("Seidel", common::LogLevel::info);
        std::vector<std::size_t> nr_parents;
        std::vector<std::size_t> nr_parents_counter;

        Seidel(std::vector<AsyncNode *> nodes) : ExecutionBase(std::move(nodes))
        {
            parallelize = utils::Config::get<bool>("simulation.seidel.parallel");
            log.info("[{}] Parallel: {}", __func__, parallelize);

            log.trace("[{}] Setting up counters, {}pc", __func__, this->nodes.size());
            for (auto &node : this->nodes)
            {
                log.ext_trace("[{}] {} nr_parents {}", __func__, node->name, node->parents.size());
                nr_parents.push_back(node->parents.size());
                nr_parents_counter.push_back(node->parents.size());
            }
        }

        virtual void print(std::ostream &os) const
        {
            os << "Seidel:\n{}\n";
        }

        void init() override
        {
        }

        /**
         * Traverse the connection graph and invoke nodes when all parents have been invoked for this timestep.
         */
        void invoke_graph(StepData step)
        {
            log.trace("[{}] step data: {}", __func__, step.to_string());
            // track how many are currently running
            int launched = 0;
            int completed = 0;

            // start from ancestor nodes (no parents)
            log.trace("[{}] Reseting counters", __func__);
            for (int i = 0; i < nodes.size(); i++)
            {
                this->nr_parents_counter[i] = this->nr_parents[i]; // ensure no allocation
            }

            log.trace("[{}] starting all models without parents", __func__);
            for (int i = 0; i < nodes.size(); i++)
            {
                auto node = nodes[i];
                if (this->nr_parents_counter[i] == 0)
                {
                    log.debug("[{}] Invoking: {}", __func__, node->name);
                    node->async_invoke(step);
                    launched += 1;
                }
            }

            log.trace("[{}] launched {}, completed  {}", __func__, launched, completed);
            while (launched != completed)
            {
                log.trace("[{}] Waiting for nodes to finish", __func__);
                shared_state->sem.acquire();
                completed += 1;

                DoneMsg msg;
                {
                    std::lock_guard<std::mutex> lock(shared_state->mtx);
                    msg = std::move(shared_state->inbox.front());
                    shared_state->inbox.pop();
                }
                auto finished_node = nodes[msg.worker_id];
                log.trace("[{}] Node finished: {}", __func__, finished_node->name);

                // enqueue children whose all parents are invoked
                for (auto n : finished_node->children)
                {
                    AsyncNode *node = (AsyncNode *)n;
                    log.ext_trace("[{}] Evaluating child node: {}", __func__, node->name);
                    this->nr_parents_counter[node->worker_id] -= 1;
                    if (this->nr_parents_counter[node->worker_id] == 0)
                    {
                        log.debug("[{}] Node ready, invoking: {}", __func__, node->name);
                        node->async_invoke(step);
                        launched += 1;
                    }
                }
            }
            log.trace("[{}] completed", __func__, launched, completed);
        }

        uint64_t invoke(StepData step_data) override final
        {
            log.ext_trace("[{}] step data: {}", __func__, step_data.to_string());
            step_data.valid_input_time = step_data.end_time;

            invoke_graph(step_data);
            return step_data.end_time;
        }
    };

    class Jacobi final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("Jacobi", common::LogLevel::info);

        bool parallelize;

        common::ThreadPool pool{5};
        std::vector<std::future<void>> futures;

        utils::ThreadPool2 pool2{5};

        Jacobi(std::vector<AsyncNode *> nodes) : ExecutionBase(std::move(nodes))
        {
            parallelize = utils::Config::get<bool>("simulation.jacobi.parallel");
            log.info("[{}] Parallel: {}", __func__, parallelize);
        }

        virtual void print(std::ostream &os) const
        {
            os << "Jacobi:\n{}\n";
        }

        void init() override
        {
        }

        // hot path
        uint64_t invoke(StepData step_data) override final
        {
#ifdef _LOG_
            log.debug("[{}] stepdata: {}", __func__, step_data.to_string());
#endif

            // If models execute in less than 10-15 microseconds then use sequence
            auto step = StepData(step_data.start_time, step_data.end_time, step_data.timestep, step_data.start_time);
            if (parallelize)
            {
                switch (3)
                {

                case 1:
                {
                    std::for_each(std::execution::par, nodes.begin(), nodes.end(),
                                  [&](auto &model)
                                  {
                                      model->invoke(step);
                                  });
                    break;
                }
                case 2:
                {
                    for (auto &node : nodes)
                    {
                        futures.push_back(pool.enqueue([&]()
                                                       { node->invoke(step); }));
                    }
                    for (auto &f : futures)
                        f.get();
                    futures.clear();
                    break;
                }
                case 3:
                {
                    // pool2
                    // log.info("[{}] New step: {}", __func__, step_data.to_string());

                    pool2.ready(nodes.size());

                    for (auto &node : this->nodes)
                    {
                        auto ti = sim::utils::task_info{node, step};
                        pool2.enqueue(ti);
                    }

                    // log.info("[{}] Spinning", __func__);
                    // spin until done
                    bool all_done = false;
                    while (!all_done)
                    {
                        all_done = true;
                        for (int i = 0; i < pool2.dones.size(); ++i)
                        {
                            if (!pool2.dones[i])
                            {
                                all_done = false;
                                break;
                            }
                        }
                    }
                    // log.info("[{}] All done", __func__);
                }
                }
            }
            else
            {
                for (auto &model : this->nodes)
                {
                    model->invoke(step);
                }
            }

            return step_data.end_time;
        }
    };
}
