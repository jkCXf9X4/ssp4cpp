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

        std::size_t size = 0;
        std::size_t index = 0;
        std::size_t row_pos = 0;

        uint64_t timestamp = 0;
    };

    class DataRecorder
    {
    public:
        common::Logger log = common::Logger("DataRecorder", common::LogLevel::info);

        std::ofstream file;
        std::thread worker;

        std::atomic<bool> running;
        std::mutex event_mutex;
        std::condition_variable event;

        std::vector<Tracker> trackers;
        std::size_t tracker_index = 0;

        std::uint16_t head = 0;
        std::size_t new_item_counter = 0;
        const std::size_t rows = 20;

        std::size_t row_size = 0;

        std::map<std::uint64_t, std::uint64_t> row_time_map;
        std::map<std::uint64_t, std::uint64_t> time_row_map;
        std::unique_ptr<std::byte[]> data;
        vector<vector<bool>> updated_tracker; // [row][tracker] bool to signify if the tracker is updated

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
            if (storage->items > 0)
            {
                Tracker t;
                t.storage = storage;
                t.size = storage->pos;
                t.index = tracker_index;
                t.row_pos = row_size;
                trackers.push_back(t);

                row_size += storage->pos;

                log.trace("[{}] Adding tracker, storage: {}", __func__, storage->name);

                tracker_index++;
            }
        }

        inline void reset_update_status(std::size_t row)
        {
            log.ext_trace("[{}] Init", __func__);
            for (auto &t : trackers)
            {
                updated_tracker[row][t.index] = false;
            }
        }

        void print_headers()
        {
            log.ext_trace("[{}] Init", __func__);
            file << "time";
            for (const auto &tracker : trackers)
            {
                for (const auto &name : tracker.storage->names)
                {
                    file << ',' << name;
                }
            }
            file << '\n';
        }

        void init()
        {
            log.ext_trace("[{}] Init", __func__);
            auto allocation_size = row_size * rows;

            data = std::make_unique<std::byte[]>(allocation_size);
            log.ext_trace("[{}] Completed allocation", __func__);

            // ensure that all rows have the status of not updated at the start
            updated_tracker.reserve(rows);
            for (int r = 0; r < rows; r++)
            {
                vector<bool> trackers_status;
                trackers_status.reserve(trackers.size());
                for (auto &t : trackers)
                {
                    trackers_status.push_back(false);
                }

                updated_tracker.push_back(std::move(trackers_status));
                reset_update_status(r);
            }
            print_headers();
        }

        void start_recording()
        {
            log.info("[{}] Starting recording", __func__);
            running = true; // must be set before the start of the thread, otherwise it wont start
            worker = std::thread([this]()
                                 { loop(); });
            usleep(100); // wait for thread to start
        }

        void stop_recording()
        {
            log.info("[{}] Stop recording", __func__);
            running = false; // to end the loop

            usleep(100); // wait to complete eventual current runs
            update();

            if (worker.joinable())
            {
                worker.join();
            }

            // flush the rest of the memory to file
            for (int i = 1; i <= rows; i++)
            {
                print_row((head + i) % rows);
            }

            if (file.is_open())
            {
                file.close();
            }
        }

        inline byte *get_data_pos(std::size_t row, std::size_t offset)
        {
            return data.get() + row * row_size + offset;
        }

        void print_row(uint16_t row)
        {
            log.trace("[{}] Row: {}", __func__, row);
            file << row_time_map[row];
            for (const auto &tracker : trackers)
            {
                auto print_tracker = updated_tracker[row][tracker.index];

                for (int item = 0; item < tracker.storage->items; ++item)
                {
                    log.ext_trace("[{}] Printing tracker: {}, item:{}", __func__, tracker.storage->name, item);

                    auto pos = tracker.storage->positions[item];
                    auto type = tracker.storage->types[item];
                    file << ", ";
                    if (print_tracker)
                    {
                        output_string(type, get_data_pos(row, pos));
                    }
                }
            }
            file << '\n';
            // reset the status after printing the row
            reset_update_status(row);
            file.flush();
        }

        void update()
        {
            log.ext_trace("[{}] Notifying recording to update", __func__);
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
                    log.trace("[{}] Evaluating storage {} {}", __func__, tracker.storage->to_string(), tracker.storage->index);

                    auto storage = tracker.storage;

                    for (std::size_t area = 0; area < storage->areas; ++area)
                    {
                        if (storage->new_data_flags[area])
                        {
                            log.trace("[{}] Found new data; area: {}", __func__, area);

                            auto ts = storage->timestamps[area];
                            if (time_row_map.count(ts) == 0)
                            {
                                head = (head + 1) % rows;
                                if (new_item_counter >= rows)
                                {
                                    print_row(head); // print before overwriting
                                }
                                
                                new_item_counter++;

                                row_time_map[head] = ts;
                                time_row_map[ts] = head;

                                log.trace("[{}] New row [{}] with time [{}]", __func__, head, ts);
                            }
                            auto row = time_row_map[ts];

                            updated_tracker[row][tracker.index] = true;
                            log.trace("[{}] Copying data; row {}, size: {}", __func__, row, tracker.size);

                            memcpy(get_data_pos(row, tracker.row_pos), storage->locations[area][0], tracker.size);
                            storage->new_data_flags[area] = false;
                        }
                    }
                }
            }
        }

        void output_string(DataType type, void *data)
        {
            log.ext_trace("[{}] init", __func__);
            switch (type)
            {
            case DataType::real:
                file << *(double *)data;
                break;
            case DataType::boolean:
                file << (*(bool *)data ? 1 : 0);
                break;
            case DataType::integer:
            case DataType::enumeration:
                file << *(int *)data;
                break;
            case DataType::string:
                file << *(std::string *)data;
                break;
            default:
                file << "<bin>";
                break;
            }
        }
    };
}
