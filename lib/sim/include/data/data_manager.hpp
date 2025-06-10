

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

    class RingBuffer
    {

        // cheating, this is not a ringbuffer yet...
        // allocation operation for each new data added
        // Remove when the ring buffer is done
        size_t buffer_size;
        size_t obj_size;
        std::deque<Data> buffer = {};

    public:
        RingBuffer(size_t buffer_size, size_t obj_size)
        {
            this->buffer_size = buffer_size;
            this->obj_size = obj_size;

            buffer.resize(buffer_size);
        }

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

    class DataManager
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
        size_t buffer_size; // default

        uint64_t reference_counter;
        std::vector<RingBuffer> buffers;

        DataManager() = delete;

        DataManager(size_t buffer_size)
        {
            reference_counter = 0;
            this->buffer_size = buffer_size;
        }

        // Return the reference to the data
        u_int64_t initData(size_t obj_size)
        {
            auto buffer = RingBuffer(buffer_size, obj_size);
            buffers.push_back(buffer);
            auto pos = reference_counter;
            reference_counter++;
            return pos;
        }

        void setData(u_int64_t time, u_int64_t reference, void *data)
        {
            buffers[reference].push(data, time);
        }

        void *getData(u_int64_t time, u_int64_t reference)
        {
            return buffers[reference].get_valid(time);
        }
    };
}