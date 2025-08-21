#pragma once

#include "common_log.hpp"

#include "data_storage.hpp"

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
    struct Tracker
    {
        DataStorage *storage;
        std::size_t index = 0;
        uint64_t timestamp = 0;
    };

    class DataRecorder
    {
    public:
        common::Logger log = common::Logger("DataRecorder", common::LogLevel::debug);

        std::ofstream file;
        std::thread worker;

        std::atomic<bool> running;
        std::mutex event_mutex;
        std::condition_variable event;

        std::vector<Tracker> trackers;
        std::size_t tracker_index = 0;

        DataRecorder(const std::string &filename)
            : file(filename, std::ios::out)
        {
            log.ext_trace("[{}] Constructor", __func__);
        }

        DataRecorder(const DataRecorder &) = delete;
        DataRecorder &operator=(const DataRecorder &) = delete;

        ~DataRecorder()
        {
            log.ext_trace("[{}] init", __func__);
        }

        void add_storage(DataStorage *storage)
        {
            Tracker t;
            t.storage = storage;
            t.index = tracker_index;
            trackers.push_back(t);

            log.trace("[{}] Adding tracker, storage: {}", __func__, storage->name);

            tracker_index++;
        }

        void start_recording()
        {
            log.trace("[{}] Starting recording", __func__ );
            running = true; // must be set before the start of the thread, otherwise it wont start
            worker = std::thread([this]()
                                 { loop(); });
            usleep(100); // wait for thread to start
        }

        void stop_recording()
        {
            log.trace("[{}] Stop recording", __func__ );
            running = false; // to end the loop

            usleep(100); // wait for complete eventual current runs
            update();
            
            if (worker.joinable())
            {
                worker.join();
            }
            if (file.is_open())
            {
                file.close();
            }
        }

        void print_headers()
        {
            // file << "time";
            // for (const auto &name : names)
            //     file << ',' << name;
            // file << '\n';
        }

        void update()
        {
            log.ext_trace("[{}] Notifying recording to update", __func__ );
            event.notify_all();
        }

        void loop()
        {
            log.trace("[{}] Starting recording thread", __func__);
            while (running)
            {
                // log.ext_trace("[{}] Holding on lock", __func__);
                std::unique_lock<std::mutex> lock(event_mutex);
                event.wait(lock);

                log.trace("[{}] Looking for new content to write to file", __func__);

                for (auto &tracker : trackers)
                {
                    log.ext_trace("[{}] Evaluating {}", __func__, tracker.storage->to_string());
                    
                    auto storage = tracker.storage;

                    for (std::size_t area = 0; area < storage->areas; ++area)
                    {
                        if (storage->new_data_flags[area])
                        {
                            for (std::size_t item = 0; item < storage->items; ++item)
                            {
                                int pos;
                                log.ext_trace("[{}] Writing to file", __func__);

                                record(storage->timestamps[area], tracker.index, item, storage->types[item], storage->locations[area][item]);
                            }
                            storage->new_data_flags[area] = false;
                        }
                    }

                }
                file.flush();
            }
        }

        void record(uint64_t time, std::size_t tracker, uint64_t reference, DataType type, void *data)
        {
            log.ext_trace("[{}] init", __func__);
            switch (type)
            {
            case DataType::real:
                file << time << "," << tracker << "." << reference << "," << *(double *)data << "\n";
                break;
            case DataType::boolean:
                file << time << "," << tracker << "." << reference << "," << (*(bool *)data ? 1 : 0) << "\n";
                break;
            case DataType::integer:
            case DataType::enumeration:
                file << time << "," << tracker << "." << reference << "," << *(int *)data << "\n";
                break;
            case DataType::string:
                file << time << "," << tracker << "." << reference << "," << *(std::string *)data << "\n";
                break;
            default:
                file << time << "," << tracker << "." << reference << ",<bin>\n";
                break;
            }
        }
    };
}
