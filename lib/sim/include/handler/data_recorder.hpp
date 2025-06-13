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
        uint64_t data_reference;
        DataBuffer * buffer;
    };

    class DataRecorder
    {
    public:
        common::Logger log = common::Logger("DataHandler", common::LogLevel::ext_trace);

    
        std::ofstream file;
        std::thread worker;

        std::atomic<bool> running;
        std::mutex event_mutex;
        std::condition_variable *event;
        std::vector<BufferTracker> buffers;

        DataRecorder(std::condition_variable *event, const std::string &filename)
            : file(filename, std::ios::out)
        {
            log.ext_trace("[{}] Constructor", __func__);
            running = true;
            this->event = event;
            worker = std::thread([this]()
                                 { loop(); });
        }

        ~DataRecorder()
        {
            log.ext_trace("[{}] init", __func__);
            running = false;
            event->notify_all();
            if (worker.joinable())
            {
                worker.join();
            }
            if (file.is_open())
            {
                file.close();
            }
        }

        void register_buffer(DataBuffer *buffer, uint64_t ref)
        {
            log.ext_trace("[{}] Init, ref:{}", __func__, ref);
            buffers.emplace_back(BufferTracker {0, ref, buffer});
        }

        void loop()
        {
            while (running)
            {
                std::unique_lock<std::mutex> lock(event_mutex);
                event->wait(lock);
                log.ext_trace("[{}] Looking for new content to write to file", __func__);

                for (auto &tracker : buffers)
                {
                    auto buffer = tracker.buffer;
                    for (std::size_t i = 0; i < buffer->size; ++i)
                    {
                        int pos;
                        auto ts = buffer->get_time(i, pos);
                        if (ts > tracker.timestamp)
                        {
                            record(ts, tracker.data_reference, buffer->type, buffer->data_ptr(pos));
                        }
                    }
                }
            }
        }

        void record(uint64_t time, uint64_t reference, DataType type, void* data)
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
