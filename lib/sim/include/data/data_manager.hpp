

#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <map>
#include <stdexcept>

namespace ssp4cpp::sim::data
{

    /**
     * @brief Simple wrapper owning a memory block with an associated timestamp.
     */
    class Data
    {
    private:
        size_t size;

    public:
        void *data;
        u_int64_t timestamp;

        Data(size_t size)
        {
            this->size = size;
            data = malloc(size);
        }
        ~Data()
        {
            free(data);
        }

        void setData(void *obj)
        {
            std::memcpy(data, obj, size);
        }
    };

    /**
     * @brief Very small ring buffer implementation used for time stamped data.
     */
    class RingBuffer
    {

        // cheating, this is not a ringbuffer yet...
        // allocation operation for each new data added
        // Remove when the ring buffer is done
        size_t buffer_size;
        size_t obj_size;
        std::deque<Data> buffer = {};

    public:
        /** Construct a ring buffer with capacity for @p buffer_size elements. */
        RingBuffer(size_t buffer_size, size_t obj_size)
        {
            this->buffer_size = buffer_size;
            this->obj_size = obj_size;

            buffer.resize(buffer_size);
        }

        /** Insert a copy of the given object at timestamp @p time. */
        void push(void *obj, u_int64_t time)
        {

            auto d = Data(obj_size);

            d.setData(obj);
            d.timestamp = time;

            buffer.push_front(d);
            while (buffer.size() > buffer_size)
            {
                buffer.pop_back();
            }
        }

        /** Retrieve the most recent element with timestamp not newer than @p time. */
        void *get_valid(u_int64_t time)
        {
            // Return the first item where the timestamp is made prior to the time
            for (Data n : buffer)
            {
                if (n.timestamp <= time)
                {
                    return n.data;
                }
            }
            return nullptr;
        }
    };

    /**
     * @brief Manages multiple ring buffers identified by a reference id.
     */
    class DataManager
    {
        /*
        All timestamps will be for when the data was created

        Time A -> execution of model -> time B
        setData will use 'time B'

        getData will use 'time A'
        This to ensure that only valid data is used


        */
        size_t buffer_size = 10; // default

        uint64_t reference_counter;
        std::vector<RingBuffer> buffers;

        /** Create a DataManager with given ring buffer size. */
        DataManager(size_t buffer_size)
        {
            reference_counter = 0;
            this->buffer_size = buffer_size;
        }

        // Return the reference to the data
        /** Allocate a new buffer for objects of size @p obj_size and return its reference id. */
        u_int64_t initData(size_t obj_size)
        {
            auto buffer = RingBuffer(buffer_size, obj_size);
            buffers.push_back(buffer);
            auto pos = reference_counter;
            reference_counter++;
            return pos;
        }

        /** Push a new sample into the buffer identified by @p reference. */
        void setData(u_int64_t time, u_int64_t reference, void *data)
        {
            buffers[reference].push(data, time);
        }

        /** Retrieve the latest valid sample from a buffer. */
        void *getData(u_int64_t time, u_int64_t reference)
        {
            return buffers[reference].get_valid(time);
        }
    };
}