
#pragma once

#include <atomic>
#include <cstdint>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <optional>
#include <semaphore>
#include <stack>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

#include "common_log.hpp"

#include "async_node.hpp"

namespace ssp4cpp::sim::utils
{
    struct task_info
    {
        graph::AsyncNode *node;
        graph::StepData step;
        // uint64_t result;
    };
    /**
     * @brief Simple thread pool for executing queued tasks.
     */
    class ThreadPool2
    {
    private:
        common::Logger log = common::Logger("common::ThreadPool", common::LogLevel::trace);

        std::mutex mtx;
        std::condition_variable cv;

        std::mutex queue_mutex;
        std::vector<std::thread> workers;

        std::stack<task_info> tasks;

        size_t que = 0;
        std::size_t epoch = 0; //  gate flag shared by all threads

        std::atomic<bool> terminate{false};

    public:
        std::vector<std::atomic<bool>> dones;

        ThreadPool2(size_t num_threads) : dones(num_threads)
        {
            workers.reserve(num_threads);
            for (int i = 0; i < num_threads; ++i)
            {
                dones[i] = false;
                workers.emplace_back(&ThreadPool2::worker_thread, this, i, std::ref(dones[i]));
            }
            log.debug("[{}] Threads started", __func__);
        }

        /**
         * @brief terminate all worker threads and wait for completion.
         */
        ~ThreadPool2()
        {
            log.debug("[{}] Destroying threadpool", __func__);
            terminate.store(true);

            // Wake everyone so they see terminate==true
            {
                std::lock_guard<std::mutex> lk(mtx);
                ++epoch; // bump to ensure all waiting threads re-check predicate
            }
            cv.notify_all();

            log.debug("[{}] Waiting for all tasks to complete", __func__);
            for (std::thread &worker : workers)
            {
                if (worker.joinable())
                {
                    worker.join();
                }
            }
            log.debug("[{}] Threadpool successfully destroyed", __func__);
        }

        void ready(int nodes)
        {
            // log.debug("[{}] Ready", __func__);
            for (int i = 0; i < workers.size(); ++i)
            {
                dones[i] = false;
            }

            {
                std::lock_guard<std::mutex> lock(mtx);
                que = nodes;
                ++epoch;
            }
            cv.notify_all();
        }

        /**
         * @brief Queue a new task for execution.
         *

         * @return Future representing the result of the task.
         */
        void enqueue(task_info &task)
        {

            // log.debug("[{}] Enqueueing task: {}", __func__, task.node->name);
            {
                std::scoped_lock lock(queue_mutex);
                tasks.emplace(std::move(task));
            }
            // log.debug("[{}] Task queued: {}", __func__, task.node->name);
        }

    private:
        /**
         * @brief Function executed by each worker thread to process tasks.
         */
        void worker_thread(int id, std::atomic<bool> &done)
        {
            std::size_t my_epoch = 0;

            while (true)
            {
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [&]
                            { return epoch != my_epoch; }); // safe, atomic, and race-free
                    my_epoch = epoch;                       // observe the generation we woke for
                }

                if (terminate.load())
                    break;

                while (true)
                {
                    std::optional<task_info> task;

                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        if (que == 0)
                            break;

                        if (!tasks.empty())
                        {
                            // log.debug("[{}] Found new task, que {}", __func__, que);
                            task = std::move(tasks.top());
                            tasks.pop();
                            --que;
                        }
                    }

                    if (task)
                    {
                        auto &t = task.value();
                        // log.debug("[{}] Invoking {} {}", __func__, t.node->name, t.step.to_string());
                        t.node->invoke(t.step);
                        // log.debug("[{}] Task completed {}", __func__, t.node->name);
                    }
                }
                done = true;
            }

            log.debug("[{}] Thread finished", __func__);
        }
    };

} // namespace ssp4cpp::sim::utils
