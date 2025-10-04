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

    class JacobiSerial final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("JacobiSerial", common::LogLevel::info);

        JacobiSerial(std::vector<AsyncNode *> nodes) : ExecutionBase(std::move(nodes))
        {
            log.info("[{}] ", __func__);
        }

        virtual void print(std::ostream &os) const
        {
            os << "JacobiSerial:\n{}\n";
        }

        void init() override
        {
        }

        // static void run(IModel &model, StepData &step)
        // {
        //     model.pre(step.start_time ,data.valid_input_time);

        //     auto end_t = model.step(step.end_time);

        //     model.post(end_t);
        // } 

        // hot path
        uint64_t invoke(StepData step_data) override final
        {
#ifdef _LOG_
            log.debug("[{}] stepdata: {}", __func__, step_data.to_string());
#endif

            auto step = StepData(step_data.start_time, step_data.end_time, step_data.timestep, step_data.start_time);

            for (auto &model : this->nodes)
            {
                model->invoke(step);
            }

            return step_data.end_time;
        }
    };

    class JacobiParallelFutures final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("JacobiParallelFutures", common::LogLevel::info);

        common::ThreadPool pool;
        std::vector<std::future<void>> futures;

        JacobiParallelFutures(std::vector<AsyncNode *> nodes, int threads) : ExecutionBase(std::move(nodes)), pool(threads)
        {
            log.info("[{}] JacobiParallelFutures", __func__);
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
            auto step = StepData(step_data.start_time, step_data.end_time, step_data.timestep, step_data.start_time);

            for (auto &node : nodes)
            {
                futures.push_back(pool.enqueue([&]()
                                               { node->invoke(step); }));
            }
            for (auto &f : futures)
                f.get();
            futures.clear();

            return step_data.end_time;
        }
    };

    class JacobiParallelTBB final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("JacobiParallelTBB", common::LogLevel::info);

        JacobiParallelTBB(std::vector<AsyncNode *> nodes) : ExecutionBase(std::move(nodes))
        {
            log.info("[{}] JacobiParallelTBB", __func__);
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
            auto step = StepData(step_data.start_time, step_data.end_time, step_data.timestep, step_data.start_time);

            std::for_each(std::execution::par, nodes.begin(), nodes.end(),
                          [&](auto &model)
                          {
                              model->invoke(step);
                          });
            return step_data.end_time;
        }
    };

    class JacobiParallelSpin final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("JacobiParallelSpin", common::LogLevel::info);

        utils::ThreadPool2 pool;

        JacobiParallelSpin(std::vector<AsyncNode *> nodes, int threads) : ExecutionBase(std::move(nodes)), pool(threads)
        {
            log.info("[{}] JacobiParallelSpin", __func__);
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
            auto step = StepData(step_data.start_time, step_data.end_time, step_data.timestep, step_data.start_time);

            pool.ready(nodes.size());

            for (auto &node : nodes)
            {
                auto ti = sim::utils::task_info{node, step};
                pool.enqueue(ti);
            }
#ifdef _LOG_
            log.info("[{}] Spinning until all threads are done", __func__);
#endif
            bool all_done = false;
            while (!all_done)
            {
                all_done = true;
                for (int i = 0; i < pool.dones.size(); ++i)
                {
                    if (!pool.dones[i])
                    {
                        all_done = false;
                        break;
                    }
                }
            }
#ifdef _LOG_
            log.info("[{}] All threads completed", __func__);
#endif
            return step_data.end_time;
        }
    };
}
