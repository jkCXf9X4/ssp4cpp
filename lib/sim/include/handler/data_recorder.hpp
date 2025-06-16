#pragma once

#include "data_buffer.hpp"
#include "data_type.hpp"
#include "common_log.hpp"

#include <fstream>
#include <mutex>
#include <thread>
#include <atomic>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace ssp4cpp::sim::handler
{
    struct BufferTracker
    {
        uint64_t timestamp = 0;
        DataBuffer *buffer;
    };

    class DataRecorder
    {
    public:
        common::Logger log = common::Logger("DataRecorder", common::LogLevel::ext_trace);

        std::ofstream file;
        std::thread worker;

        std::atomic<bool> running;
        std::mutex event_mutex;
        std::condition_variable event;

        std::vector<BufferTracker> buffers;

        DataRecorder(const std::string &filename)
            : file(filename, std::ios::out)
        {
            log.ext_trace("[{}] Constructor", __func__);
            running = true;

            worker = std::thread([this]()
                                 { loop(); });
            usleep(100); // wait for thred to start
        }

        DataRecorder(const DataRecorder&) = delete;
        DataRecorder &operator=(const DataRecorder &) = delete;

        ~DataRecorder()
        {
            log.ext_trace("[{}] init", __func__);
            running = false;
            event.notify_all();
            if (worker.joinable())
            {
                worker.join();
            }
            if (file.is_open())
            {
                file.close();
            }
            log.ext_trace("[{}] completed", __func__);
        }

        void register_buffer(DataBuffer *buffer)
        {
            log.ext_trace("[{}] Init", __func__);
            buffers.emplace_back(BufferTracker{0, buffer});
        }

        auto get_register_buffer_callback()
        {
            return [this](auto &&...args)
            {
                register_buffer(std::forward<decltype(args)>(args)...);
            };
        }

        void update()
        {
            event.notify_all();
        }

        auto get_update_callback()
        {
            return [this]()
            {
                update();
            };
        }

        void loop()
        {
            while (true)
            {
                std::unique_lock<std::mutex> lock(event_mutex);
                event.wait(lock);
                if (!running)
                {
                    // make sure that the buffers are not evaluated
                    // there is no guarantee that the pointers are still valid
                    return;
                }

                log.ext_trace("[{}] Looking for new content to write to file", __func__);
                
                for (auto &tracker : buffers)
                {
                    log.ext_trace("[{}] Evaluating {}", __func__, tracker.buffer->name);
                    auto buffer = tracker.buffer;
                    uint64_t max_time = tracker.timestamp;
                    for (std::size_t i = 0; i < buffer->size; ++i)
                    {
                        log.ext_trace("[{}] i:{}", __func__, i);
                        int pos;
                        auto ts = buffer->get_time(i, pos);
                        if (ts > tracker.timestamp)
                        {
                            log.ext_trace("[{}] Writing t: {} to file", __func__, ts);
                            record(ts, buffer->data_reference, buffer->type, buffer->data_ptr(pos));
                            if (ts > max_time)
                            {
                                max_time = ts;
                            }
                        }
                    }
                    tracker.timestamp = max_time;
                }
            }
        }

        void record(uint64_t time, uint64_t reference, DataType type, void *data)
        {
            log.ext_trace("[{}] init", __func__);
            switch (type)
            {
            case DataType::BOOL:
                file << time << "," << reference << "," << (*(bool *)data ? 1 : 0) << "\n";
                break;
            case DataType::INT:
            case DataType::ENUM:
                file << time << "," << reference << "," << *(int *)data << "\n";
                break;
            case DataType::REAL:
                file << time << "," << reference << "," << *(double *)data << "\n";
                break;
            case DataType::STRING:
                file << time << "," << reference << "," << *(std::string *)data << "\n";
                break;
            default:
                file << time << "," << reference << ",<bin>\n";
                break;
            }
            file.flush();
        }
    };
}
