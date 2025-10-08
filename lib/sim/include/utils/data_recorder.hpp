#pragma once

#include "common_log.hpp"
#include "common_time.hpp"

#include "common_definitions.hpp"

#include "data_storage.hpp"
#include "config.hpp"

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


/*
* Solution build upon that both input and outputs are stored in the same row, if not then the output file will be incomplete....

* new solution is needed later....

* @todo: Log everything that is between +-2 steps from the print time to ensure that no data is lost but still avoiding to log everything
*/

    class DataRecorder
    {
    public:
        common::Logger log = common::Logger("ssp4sim.utils.DataRecorder", common::LogLevel::info);

        std::ofstream file;
        std::unique_ptr<std::thread> worker;

        std::atomic<bool> running;
        std::mutex event_mutex;
        std::condition_variable event;

        std::vector<Tracker> trackers;
        std::size_t tracker_index = 0;

        std::uint16_t head = 0;
        std::size_t new_item_counter = 0;
        const std::size_t rows = 50;

        std::size_t row_size = 0;

        std::map<std::uint64_t, std::uint64_t> row_time_map;
        std::map<std::uint64_t, std::uint64_t> time_row_map;
        std::unique_ptr<std::byte[]> data;
        std::vector<std::vector<bool>> updated_tracker; // [row][tracker] bool to signify if the tracker is updated

        const uint64_t recording_interval = common::time::s_to_ns(utils::Config::getOr<double>("simulation.result_interval", 1.0));
        uint64_t last_print_time = 0;
        size_t printed_rows = 0;

        DataRecorder(const std::string &filename)
            : file(filename, std::ios::out)
        {
            log.ext_trace("[{}] Constructor", __func__);

            log.debug("[{}] Recording interval {}", __func__, recording_interval);
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
                std::vector<bool> trackers_status;
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
            worker = std::make_unique<std::thread>([this]()
                                                   { loop(); });
            usleep(100); // wait for thread to start
        }

        void stop_recording()
        {
            log.info("[{}] Stop recording", __func__);
            if (!running)
            {
                return;
            }

            running = false; // to end the loop

            usleep(100); // wait to complete eventual current runs
            update();

            if (worker->joinable())
            {
                worker->join();
            }

            // flush the rest of the memory to file
            for (int i = 1; i <= rows; i++)
            {
                bool print = false;
                auto row = (head + i) % rows;
                for (auto &tracker : trackers)
                {
                    if (updated_tracker[row][tracker.index])
                    {
                        print = true;
                    }
                }
                if (print)
                {
                    print_row(row);
                }
            }
            file.flush();

            if (file.is_open())
            {
                file.close();
            }
        }

        inline std::byte *get_data_pos(std::size_t row, std::size_t offset)
        {
            return data.get() + row * row_size + offset;
        }

        void print_row(uint16_t row)
        {
            IF_LOG({
                log.trace("[{}] Row: {}", __func__, row);
            });

            auto time = common::time::ns_to_s(row_time_map[row]);

            file << time;
            for (const auto &tracker : trackers)
            {
                auto print_tracker = updated_tracker[row][tracker.index];

                for (int item = 0; item < tracker.storage->items; ++item)
                {
                    IF_LOG({
                        log.ext_trace("[{}] Printing tracker: {}, item:{}", __func__, tracker.storage->name, item);
                    });

                    auto pos = tracker.storage->positions[item];
                    auto type = tracker.storage->types[item];
                    file << ", ";
                    if (print_tracker)
                    {
                        auto data_type_str = fmi2::ext::enums::data_type_to_string(type, get_data_pos(row, tracker.row_pos + pos));
                        file << data_type_str;
                    }
                }
            }
            file << '\n';
            printed_rows += 1;

            // Flush to file only once in a while to save on disk writes
            if (printed_rows % 50 == 0)
            {
                file.flush();
            }
        }

        void update()
        {
            log.ext_trace("[{}] Notifying recording to update", __func__);
            // to slow, removed
            // event.notify_all();
        }

        void loop()
        {
            log.debug("[{}] Starting recording thread", __func__);

            // spinn, spinn!
            while (running)
            {
                IF_LOG({
                    log.ext_trace("[{}] Looking for new content to write to file", __func__);
                });

                for (auto &tracker : trackers)
                {
                    IF_LOG({
                        log.ext_trace("[{}] Evaluating storage {} {}", __func__, tracker.storage->to_string(), tracker.storage->index);
                    });

                    for (std::size_t area = 0; area < tracker.storage->areas; ++area)
                    {
                        auto storage = tracker.storage;
                        if (storage->new_data_flags[area])
                        {

                            IF_LOG({
                                log.trace("[{}] Found new data; area: {}", __func__, area);
                            });

                            process_new_data(tracker, storage, area);
                            // reset the status after processing the row
                            storage->new_data_flags[area] = false;
                        }
                    }
                }
            }

            log.debug("[{}] Exiting recording thread", __func__);
        }

        void process_new_data(ssp4cpp::sim::utils::Tracker &tracker, sim::utils::DataStorage *storage, std::size_t area)
        {

            auto ts = storage->timestamps[area];

            // is it time to add a new row for printing?
            if (ts >= last_print_time + recording_interval)
            {
                IF_LOG({
                    log.trace("[{}] New print time: {}, last_print_time {}", __func__, ts, last_print_time);
                });

                last_print_time += recording_interval;

                head = (head + 1) % rows;
                if (new_item_counter >= rows) [[likely]]
                {
                    IF_LOG({
                        log.trace("[{}] Row already in use, print and reset. {}", __func__, head);
                    });

                    print_row(head); // print before overwriting
                    reset_update_status(head);
                }

                new_item_counter++;

                row_time_map[head] = ts;
                time_row_map[ts] = head;
                IF_LOG({
                    log.trace("[{}] New row [{}] with time [{}]", __func__, head, ts);
                });
            }

            if (time_row_map.contains(ts))
            {
                auto row = time_row_map[ts];
                IF_LOG({
                    log.trace("[{}] Copying new data; row {}, size: {}", __func__, row, tracker.size);
                });

                memcpy(get_data_pos(row, tracker.row_pos), storage->locations[area][0], tracker.size);
                updated_tracker[row][tracker.index] = true;
            }
        }
    };
}
