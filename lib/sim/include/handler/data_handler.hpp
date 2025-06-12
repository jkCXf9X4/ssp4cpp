

#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

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

    enum class DataType
    {
        BOOL,
        INT,
        REAL,
        STRING,
        ENUM,
        UNKNOWN
    };

    /**
     * @brief  Return the in-memory size (in bytes) of a single value
     *         represented by the given DataType.
     */
    constexpr std::size_t get_data_type_size(DataType t)
    {
        switch (t)
        {
        case DataType::BOOL:
            return sizeof(bool); // typically 1
        case DataType::INT:
            return sizeof(int); // typically 4
        case DataType::REAL:
            return sizeof(double); // typically 8
        case DataType::ENUM:
            return sizeof(int); // stored like an int
        case DataType::STRING:
            return sizeof(std::string);
        case DataType::UNKNOWN:
            return 0;
        }
        // If the enum gains a new value and the switch isn’t updated,
        // this keeps the compiler happy in -Wall/-Wswitch-enums builds.
        throw std::invalid_argument("Unknown DataType");
    }

    /**
     * @brief Very small ring buffer implementation used for time stamped data.
     * When full it will continuously overwrite the oldest data
     */
    class RingBuffer
    {
        DataType type = DataType::UNKNOWN;
        std::unique_ptr<std::byte[]> data; // raw storage
        std::unique_ptr<uint64_t[]> timestamps;

        size_t obj_size;

        size_t capacity; /* total usable slots                 */
        size_t head;     /* next position to write             */
        size_t size;     /* current number of elements stored  */

    public:
        /** Construct a ring buffer with capacity for @p buffer_size elements. */
        RingBuffer(size_t capacity, size_t obj_size, DataType type)
        {
            if (capacity == 0)
            {
                throw runtime_error("[RingBuffer] buffer_size != 0");
            }
            this->capacity = capacity;
            this->type = type;
            if (type != DataType::UNKNOWN)
            {
                this->obj_size = get_data_type_size(type);
            }
            else
            {
                this->obj_size = obj_size;
            }

            data = std::make_unique<std::byte[]>(obj_size * capacity);
            timestamps = std::make_unique<uint64_t[]>(sizeof(uint64_t) * capacity);

            if (!data || !timestamps)
                throw runtime_error("Failed to allocate Data");

            head = size = 0;
        }

        bool is_empty()
        {
            return size == 0;
        }

        bool is_full()
        {
            return size == capacity;
        }

        // Add new, if full it will overwrite the oldest data
        int push(void *obj, uint64_t time)
        {
            if (!is_full()) [[unlikely]]
            {
                size++;
            }

            std::memcpy(data.get() + head * obj_size, obj, obj_size);
            timestamps[head] = time;

            head = (head + 1) % capacity;
            return 0;
        }

        /** Retrieve the most recent element with timestamp not newer than @p time. */
        void *get_valid(uint64_t time)
        {
            for (std::size_t k = 0; k < size; ++k)
            {
                std::size_t idx = (head + capacity - 1 - k) % capacity; // newest → oldest
                if (timestamps[idx] <= time)
                {
                    return static_cast<void *>(data.get() + idx * obj_size);
                }
            }
            return nullptr;
        }
    };

    class DataHandler
    {
    public:
        /*
        Contains multiple managers for a type

        All timestamps will be for when the data was created

        Time A -> execution of model -> time B
        setData will use 'time B'

        getData will use 'time A'
        This to ensure that only valid data is used
        */
        size_t buffer_size;

        uint64_t reference_counter;
        std::vector<unique_ptr<RingBuffer>> buffers;

        DataHandler() {}

        DataHandler(size_t buffer_size)
        {
            reference_counter = 0;
            this->buffer_size = buffer_size;
        }

        // Return the reference to the data
        /** Allocate a new buffer for objects of type @p type */
        uint64_t initData(DataType type)
        {
            // size not needed for known types
            auto buffer = make_unique<RingBuffer>(buffer_size, -1, type);
            buffers.push_back(std::move(buffer));

            auto pos = reference_counter;
            reference_counter++;
            return pos;
        }

        /** Allocate a new buffer for objects of size @p obj_size and return its reference id. */
        uint64_t initData(size_t size)
        {
            auto buffer = make_unique<RingBuffer>(buffer_size, size, DataType::UNKNOWN);
            buffers.push_back(std::move(buffer));

            auto pos = reference_counter;
            reference_counter++;
            return pos;
        }

        /** Push a new sample into the buffer identified by @p reference. */
        void setData(uint64_t time, uint64_t reference, void *data)
        {
            buffers[reference]->push(data, time);
        }

        /** Retrieve the latest valid sample from a buffer. */
        void *getData(uint64_t time, uint64_t reference)
        {
            return buffers[reference]->get_valid(time);
        }
    };
}