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

namespace ssp4cpp::sim::utils
{
    // struct BufferTracker
    // {
    //     uint64_t timestamp = 0;
    //     shared_ptr<DataBuffer> buffer;
    // };

    class DataRecorder
    {
    public:
        common::Logger log = common::Logger("DataRecorder", common::LogLevel::ext_trace);

        std::ofstream file;
        std::thread worker;

        std::atomic<bool> running;
        std::mutex event_mutex;
        std::condition_variable event;

        std::vector<std::string> names;
        std::vector<pair<DataType, void *>> data;

        DataRecorder(const std::string &filename)
            : file(filename, std::ios::out)
        {
            log.ext_trace("[{}] Constructor", __func__);
            running = true;

            worker = std::thread([this]()
                                 { loop(); });
            usleep(100); // wait for thread to start
        }

        DataRecorder(const DataRecorder &) = delete;
        DataRecorder &operator=(const DataRecorder &) = delete;

        ~DataRecorder()
        {
            log.ext_trace("[{}] init", __func__);
            running = false;

            usleep(10); // give all treads the chance to return to waiting
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

        void print_headers()
        {
            file << "time";
            for (int name : names)
                file << ',' << name;
            file << '\n';
        }

        void print_data(u)

        void update()
        {
            event.notify_all();
        }

        void loop()
        {
            while (running)
            {
                std::unique_lock<std::mutex> lock(event_mutex);
                event.wait(lock);

                log.ext_trace("[{}] Looking for new content to write to file", __func__);

                for (auto &tracker : buffers)
                {
                    log.ext_trace("[{}] Evaluating {}", __func__, tracker.buffer->name);
                    auto buffer = tracker.buffer;
                    uint64_t max_time = tracker.timestamp;
                    for (std::size_t i = 0; i < buffer->size; ++i)
                    {
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
                file.flush();
            }
        }

        void record(uint64_t time, uint64_t reference, DataType type, void *data)
        {
            log.ext_trace("[{}] init", __func__);
            switch (type)
            {
            case DataType::real:
                file << time << "," << reference << "," << *(double *)data << "\n";
                break;
            case DataType::boolean:
                file << time << "," << reference << "," << (*(bool *)data ? 1 : 0) << "\n";
                break;
            case DataType::integer:
            case DataType::enumeration:
                file << time << "," << reference << "," << *(int *)data << "\n";
                break;
            case DataType::string:
                file << time << "," << reference << "," << *(std::string *)data << "\n";
                break;
            default:
                file << time << "," << reference << ",<bin>\n";
                break;
            }
        }
    };
}
