#include "common_thread_pool.hpp"

namespace ssp4cpp::common
{

    ThreadPool::ThreadPool(size_t num_threads)
        : stop(false), log("common::ThreadPool", LogLevel::info), task_semaphore(0)
    {
        for (size_t i = 0; i < num_threads; ++i)
        {
            workers.emplace_back([this]
                                 { this->worker_thread(); });
        }
        log.debug("[{}] Threads started", __func__);
    }

    ThreadPool::~ThreadPool()
    {
        log.debug("[{}] Destroying threadpool", __func__);
        stop = true; // atomic

        // release all threads to ensure that they are closing down
        for (size_t i = 0; i < workers.size(); ++i)
        {
            task_semaphore.release();
        }

        log.debug("[{}] Waiting for all tasks to complete", __func__);
        for (std::thread &worker : workers)
        {
            worker.join();
        }
        log.debug("[{}] Threadpool successfully destroyed", __func__);
    }

    void ThreadPool::worker_thread()
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

                log.debug("[{}] Task starting", __func__);
                task = std::move(tasks.front());
                tasks.pop();
            }
            task();
            log.debug("[{}] Task completed", __func__);
        }

        log.debug("[{}] Thread finished", __func__);
    }

} // namespace common
