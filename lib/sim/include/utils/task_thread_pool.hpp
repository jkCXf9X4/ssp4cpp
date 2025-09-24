
#pragma once

#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <semaphore>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>
#include <cstdint>

#include "common_log.hpp"

namespace ssp4cpp::common
{

    /**
     * @brief Simple thread pool for executing queued tasks.
     */
    class ThreadPool
    {
    private:
        Logger log = Logger("common::ThreadPool", LogLevel::info);

        std::mutex queue_mutex;
        std::vector<std::thread> workers;

        std::queue<std::function<void()>> tasks;
        std::counting_semaphore<> task_semaphore{0};
        bool stop = false;

    public:
        ThreadPool(size_t num_threads)
        {
            workers.reserve(num_threads);
            for (size_t i = 0; i < num_threads; ++i)
            {
                workers.emplace_back([this]
                                     { worker_thread(); });
            }
            log.debug("[{}] Threads started", __func__);
        }

        /**
         * @brief Stop all worker threads and wait for completion.
         */
        ~ThreadPool()
        {
            log.debug("[{}] Destroying threadpool", __func__);
            stop = true;

            // release all threads to ensure that they are closing down
            // The que will always be empty when this occurs
            task_semaphore.release(static_cast<std::ptrdiff_t>(workers.size()));

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

        /**
         * @brief Queue a new task for execution.
         *

         * @return Future representing the result of the task.
         */
        template <class F>
        auto enqueue(F &&f)
        {
            using return_type = std::invoke_result_t<F>;

            // log.debug("[{}] Enqueueing task", __func__);
            auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));
            std::future<return_type> res = task->get_future();

            {
                std::scoped_lock lock(queue_mutex);
                tasks.emplace([task = std::move(task)]() mutable
                              { (*task)(); });
            }

            // notify a worker that one task is available
            task_semaphore.release();

            // log.debug("[{}] Task queued", __func__);
            return res;
        }

    private:
        /**
         * @brief Function executed by each worker thread to process tasks.
         */
        void worker_thread()
        {
            while (true)
            {
                task_semaphore.acquire();

                if (stop)
                {
                    break;
                }

                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    if (!tasks.empty())
                    {
                        // log.debug("[{}] Task starting", __func__);
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                }

                task();
                // log.debug("[{}] Task completed", __func__);
            }

            log.debug("[{}] Thread finished", __func__);
        }
    };

} // namespace ssp4cpp::common
