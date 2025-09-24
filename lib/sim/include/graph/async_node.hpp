#pragma once

#include "common_node.hpp"
#include "common_log.hpp"

#include "invocable.hpp"

#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <queue>
#include <semaphore> // std::counting_semaphore
#include <condition_variable>

namespace ssp4cpp::sim::graph
{

    // A wrapper to get async behavior of a node

    enum class ModelStatus
    {
        initialization,
        ready,     // waiting for execution
        running,   // executing
        completed, // completed execution, can go to ready again or exit
        exit       //
    };

    struct DoneMsg
    {
        int worker_id;
        uint64_t time;
    };

    struct SharedState
    {
        std::mutex mtx;
        std::queue<DoneMsg> inbox;
        std::counting_semaphore<> sem{0}; // initially zero permits
    };

    class AsyncNode final : public Invocable
    {

    public:
        common::Logger log = common::Logger("AsyncNode", common::LogLevel::info);

        std::thread worker;
        int worker_id;
        std::atomic<bool> running;

        std::unique_ptr<Invocable> invocable_obj;
        std::atomic<ModelStatus> status;

        StepData input;
        uint64_t output;

        SharedState *shared_state;
        std::counting_semaphore<> sem{0}; // initially zero permits

        AsyncNode(std::string name, std::unique_ptr<Invocable> m) : invocable_obj(std::move(m))
        {
            this->name = name;
            status = ModelStatus::initialization;
        }

        ~AsyncNode()
        {
            log.ext_trace("[{}] Destroying AsyncNode", __func__);
            running = false; // to end the loop

            usleep(100); // wait to complete eventual current runs
            sem.release();

            if (worker.joinable())
            {
                worker.join();
            }
        }

        virtual void print(std::ostream &os) const
        {
            os << "AsyncNode { \n"
               << "Name: " << name
               << "\n}\n";
        }
        void set_shared_state(int worker_id, SharedState *ss)
        {
            this->worker_id = worker_id;
            this->shared_state = ss;
        }

        void loop()
        {
            log.info("[{}] Starting async node thread, {}", __func__, this->name);
            while (true)
            {
#ifndef NDEBUG
                log.trace("[{}] Holding node {}", __func__, this->name);
#endif
                sem.acquire();
                if (!running)
                {
                    return;
                }

                // if (status == ModelStatus::ready)
                {
#ifndef NDEBUG
                    log.trace("[{}] Executing, node {}", __func__, this->name);
#endif
                    status = ModelStatus::running;

                    output = invoke(input);
#ifndef NDEBUG
                    log.trace("[{}] Execution completed, node {}", __func__, this->name);
#endif
                    status = ModelStatus::completed;
                    {
                        std::lock_guard<std::mutex> lock(shared_state->mtx);
                        shared_state->inbox.push({worker_id, output});
                    }
                    shared_state->sem.release(); // signal main thread
                    status = ModelStatus::ready;
                }
            }
            log.trace("[{}] Exiting async node thread, node {}", __func__, this->name);
            status = ModelStatus::exit;
        }

        void init() override final
        {
            log.trace("[{}] Init, node {}", __func__, this->name);
            this->invocable_obj->init();

            status = ModelStatus::ready;

            running = true; // must be set before the start of the thread, otherwise it wont start
            worker = std::thread([this]()
                                 { loop(); });
            usleep(100); // wait for thread to start
        }

        // hot path
        uint64_t invoke(StepData step_data) override final
        {
#ifndef NDEBUG
            log.ext_trace("[{}] Invoking async, model: {} stepdata: {}", __func__, this->name, step_data.to_string());
#endif

            return invocable_obj->invoke(step_data);
        }

        // hot path
        void async_invoke(StepData step_data)
        {
#ifndef NDEBUG
            log.trace("[{}] Invoking async, model {} start time {}", __func__, this->name, step_data.start_time);
#endif
            input = step_data;
            if (status == ModelStatus::ready)
            {
                sem.release();
            }
            else
            {
                log.warning("[{}] Unable to start model {}, its not ready", __func__, this->name);
            }
        }
    };
}