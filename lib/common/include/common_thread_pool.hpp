
#pragma once

#include "common_log.hpp"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <semaphore>

namespace ssp4cpp::common
{

    /**
     * @brief Simple thread pool for executing queued tasks.
     */
    class ThreadPool
    {
    private:
        Logger log;

        std::mutex queue_mutex;
        std::condition_variable condition;
        std::vector<std::thread> workers;

        
        std::queue<std::function<void()>> tasks;
        bool stop;

        std::counting_semaphore<> task_semaphore;

    public:
        ThreadPool(size_t num_threads);

        /**
         * @brief Stop all worker threads and wait for completion.
         */
        ~ThreadPool();

        /**
         * @brief Queue a new task for execution.
         *
         * @tparam F   Callable type.
         * @tparam Args Argument types to forward to the callable.
         * @return Future representing the result of the task.
         */
        template <class F, class... Args>
        auto enqueue(F &&f, Args &&...args)
        {
            using return_type = typename std::invoke_result<F, Args...>::type;
            log.debug("[{}] Enqueueing task", __func__);
            
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...));

            std::future<return_type> res = task->get_future();

            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                tasks.emplace([task]() { (*task)(); });
            }
            
            task_semaphore.release();
            
            log.debug("[{}] Notifying task to start (semaphore)", __func__);
            return res;
        }
        
    private:
        /**
         * @brief Function executed by each worker thread to process tasks.
         */
        void worker_thread();

    };

} // namespace common
