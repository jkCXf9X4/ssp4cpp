#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

#include "data_storage.hpp"

#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <map>
#include <stdexcept>
#include <iostream>

// Data in this case means data passed around between models as input/output
namespace ssp4cpp::sim::utils
{
    using namespace std;

    /**
     * @brief Very small ring buffer implementation used for timestamped data.
     * When full it will continuously overwrite the oldest data
     */
    class RingStorage
    {

        common::Logger log = common::Logger("RingStorage", common::LogLevel::debug);
        public:

        
        DataStorage data;

        size_t head; /* next position to write             */
        size_t tail; /* first data position      */

        size_t capacity; /* total usable slots                 */
        size_t size;     /* current number of elements stored  */
        uint64_t access_counter; // how many times has data been added

        RingStorage(size_t capacity) : data(capacity)
        {
            log.ext_trace("[{}] Constructor", __func__);
            if (capacity == 0)
            {
                throw runtime_error("[RingBuffer] buffer_size != 0");
            }
            this->capacity = capacity;
            head = tail = size = access_counter = 0;
        }

        uint64_t add(std::string name, utils::DataType type)
        {
            return data.add(name, type);
        }
        void allocate()
        {
            data.allocate();
        }

        int push(uint64_t time)
        {
            auto h = push();
            set_time(time);
            return h;
        }

        // return the latest item
        byte *get_item(std::size_t index)
        {
            return data.locations[head][index];
        }

        byte *get_item(std::size_t area, std::size_t index)
        {
            return data.locations[area][index];
        }

        byte *get_valid_item(uint64_t time, std::size_t index)
        {
            auto valid_area = get_valid_area(time);
            if (valid_area != -1)
            {
                return data.locations[valid_area][index];
            }
            return nullptr;
        }

    private:
        inline bool is_empty()
        {
            return size == 0;
        }

        inline bool is_full()
        {
            return size == capacity;
        }

        inline void set_time(uint64_t time)
        {
            data.timestamps[head] = time;
        }

        // create new, if full it will overwrite the oldest data
        int push()
        {
            log.ext_trace("[{}] init", __func__);

            if (is_full()) [[likely]]
            {
                tail = (tail + 1) % capacity;
            }
            else [[unlikely]]
            {
                size++;
            }

            // increase head
            head = (head + 1) % capacity;
            access_counter += 1;
            return head;
        }

        /** Retrieve the most recent element with timestamp before @p time. */
        int64_t get_valid_area(uint64_t time)
        {
            log.ext_trace("[{}] init", __func__);
            for (std::size_t i = 0; i < size; ++i)
            {
                int pos = get_pos_rev(i);
                if (data.timestamps[pos] <= time)
                {
                    return pos;
                }
            }
            return -1;
        }

        /* Return element at logical position `index` from the tail (oldest)     */
        inline uint64_t get_pos(int index)
        {
            return (tail + index) % capacity;
        }

        /* Return element at logical position `index` counting backwards from
        the head: index 0 == newest (just before head), 1 == next-newest, …   */
        inline uint64_t get_pos_rev(int index)
        {
            return (head + capacity - 1 - index) % capacity;
        }
    };
}