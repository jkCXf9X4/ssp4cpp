

#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

#include "data_type.hpp"

#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <map>
#include <stdexcept>
#include <iostream>

// Data in this case means data passed around between models as input/output
namespace ssp4cpp::sim::handler
{
    using namespace std;

    struct Data
    {
        uint64_t timestamp;
        std::unique_ptr<std::byte[]> data;
    };

    /**
     * @brief Very small ring buffer implementation used for time stamped data.
     * When full it will continuously overwrite the oldest data
     */
    class DataBuffer
    {
        common::Logger log = common::Logger("DataBuffer", common::LogLevel::ext_trace);

    public:
        DataType type = DataType::UNKNOWN;
        uint64_t data_reference = 0;
        std::string name = "";

        std::unique_ptr<std::byte[]> data; // raw storage
        std::unique_ptr<uint64_t[]> timestamps;

        uint64_t counter;

        size_t obj_size;

        size_t head; /* next position to write             */
        size_t tail; /* first data position      */

        size_t capacity; /* total usable slots                 */
        size_t size;     /* current number of elements stored  */
        /** Construct a ring buffer with capacity for @p buffer_size elements. */
        DataBuffer(size_t capacity, DataType type, uint64_t data_reference, std::string name)
        {
            log.ext_trace("[{}] Constructor {}", __func__, (int)type);
            if (capacity == 0)
            {
                throw runtime_error("[RingBuffer] buffer_size != 0");
            }
            this->capacity = capacity;
            this->type = type;
            this->data_reference = data_reference;
            this->name = name;
   
            this->obj_size = get_data_type_size(type);
            
            log.ext_trace("[{}] Allocating data, obj_size: {}, capacity: {}", __func__, this->obj_size, capacity);
            data = std::make_unique<std::byte[]>(this->obj_size * capacity);
            timestamps = std::make_unique<uint64_t[]>(capacity);

            if (!data || !timestamps)
                throw runtime_error("Failed to allocate Data");

            head = tail = size = counter = 0;
        }

        inline bool is_empty()
        {
            return size == 0;
        }

        inline bool is_full()
        {
            return size == capacity;
        }

        inline void *data_ptr(int index)
        {
            return data.get() + index * obj_size;
        }

        // Add new, if full it will overwrite the oldest data
        int push(void *obj, uint64_t time)
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

            if (type != DataType::STRING) [[likely]]
            {
                std::memcpy(data_ptr(head), obj, obj_size);
            }
            else [[unlikely]]
            {
                // TODO: add some check for overflow
                // double check that null terminator is included
                strcpy((char *)data_ptr(head), (char *)obj);
            }

            timestamps[head] = time;

            head = (head + 1) % capacity;
            counter++;
            return 0;
        }

        /** Retrieve the most recent element with timestamp not newer than @p time. */
        void *get_valid(uint64_t time)
        {
            log.ext_trace("[{}] init", __func__);
            for (std::size_t i = 0; i < size; ++i)
            {
                int pos;
                auto timestamp = get_time_rev(i, pos);
                if (timestamp <= time)
                {
                    return data_ptr(pos);
                }
            }
            return nullptr;
        }

        /* Return element at logical position `index` from the tail (oldest)     */
        uint64_t get_time(int index, int &pos)
        {
            pos = (tail + index) % capacity; // newest → oldest
            return timestamps[pos];
        }

        /* Return element at logical position `index` counting backwards from
        the head: index 0 == newest (just before head), 1 == next-newest, …   */
        uint64_t get_time_rev(int index, int &pos)
        {
            pos = (head + capacity - 1 - index) % capacity; // newest → oldest
            return timestamps[pos];
        }
    };
}