#pragma once

#include "common_node.hpp"
#include "common_log.hpp"

#include "invocable.hpp"

#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace ssp4cpp::sim::graph
{

    enum class ModelStatus
    {
        initialization,
        ready,     // waiting for execution
        running,   // executing
        completed, // completed execution, can go to ready again or exit
        exit       //
    };

    class AsyncNode final : public InvocableNode
    {

    public:
        common::Logger log = common::Logger("AsyncNode", common::LogLevel::debug);

        std::thread worker;
        std::atomic<bool> running;
        std::mutex event_mutex;
        std::condition_variable event;

        std::unique_ptr<Invocable> invocable_obj;
        std::atomic<ModelStatus> status;

        StepData input;
        uint64_t output;

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
            event.notify_all();

            if (worker.joinable())
            {
                worker.join();
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const AsyncNode &obj)
        {
            os << "AsyncNode { \n"
               << "Name: " << obj.name << std::endl
               << " }" << std::endl;

            return os;
        }

        void loop()
        {
            log.trace("[{}] Starting async node thread", __func__);
            while (true)
            {
                // log.ext_trace("[{}] Holding on lock", __func__);
                std::unique_lock<std::mutex> lock(event_mutex);
                event.wait(lock);
                if (!running)
                {
                    return;
                }

                if (status == ModelStatus::ready)
                {
                    log.trace("[{}] Executing node", __func__);
                    status = ModelStatus::running;

                    output = invoke(input);

                    log.trace("[{}] Node execution completed", __func__);
                    status = ModelStatus::completed;
                    status = ModelStatus::ready;
                }
            }
            log.trace("[{}] Exiting async node thread", __func__);
            status = ModelStatus::exit;
        }

        void init() override final
        {
            log.trace("[{}] Node init ", __func__);
            this->invocable_obj->init();

            status = ModelStatus::ready;

            running = true; // must be set before the start of the thread, otherwise it wont start
            worker = std::thread([this]()
                                 { loop(); });
            usleep(100); // wait for thread to start
        }

        uint64_t invoke(StepData step_data) override final
        {
            log.ext_trace("[{}] stepdata: {}", __func__, step_data.to_string());

            return invocable_obj->invoke(step_data);
        }

        void async_invoke(StepData step_data)
        {
            log.ext_trace("[{}] Invoking async model", __func__);
            input = step_data;

            event.notify_all();
        }
    };
}