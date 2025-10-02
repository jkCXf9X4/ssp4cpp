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
