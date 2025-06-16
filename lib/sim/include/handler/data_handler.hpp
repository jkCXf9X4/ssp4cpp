

#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

#include "data_type.hpp"
#include "data_buffer.hpp"
#include "data_recorder.hpp"

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

    using RegisterBufferCallback = std::function<void(shared_ptr<DataBuffer>)>;
    using DataAddedCallback = std::function<void()>;

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

        common::Logger log = common::Logger("DataHandler", common::LogLevel::debug);

        size_t buffer_size;
        uint64_t reference_counter;

        std::vector<shared_ptr<DataBuffer>> buffers;

        RegisterBufferCallback register_callback = nullptr;
        DataAddedCallback new_data_callback = nullptr;

        DataHandler() = delete;

        DataHandler(size_t buffer_size)
        {
            log.ext_trace("[{}] Constructor", __func__);
            reference_counter = 0;
            this->buffer_size = buffer_size;
        }

        DataHandler(size_t buffer_size, RegisterBufferCallback register_callback, DataAddedCallback new_data_callback) : DataHandler(buffer_size)
        {
            this->register_callback = register_callback;
            this->new_data_callback = new_data_callback;
        }

        // Return the reference to the data
        /** Allocate a new buffer for objects of type @p type */
        uint64_t initData(DataType type, std::string name)
        {
            log.ext_trace("[{}] type init ", __func__);
            auto db = make_shared<DataBuffer>(buffer_size, type, reference_counter, name);
            if (register_callback)
            {
                register_callback(db);
            }

            buffers.emplace_back(std::move(db));
            return reference_counter++;
        }

        /** Push a new sample into the buffer identified by @p reference. */
        void setData(uint64_t time, uint64_t reference, void *data)
        {
            log.ext_trace("[{}] init", __func__);
            buffers[reference]->push(data, time);
            if (new_data_callback) [[likely]]
            {
                new_data_callback();
            }
        }

        /** Retrieve the latest valid sample from a buffer. */
        void *getData(uint64_t time, uint64_t reference)
        {
            log.ext_trace("[{}] init", __func__);
            return buffers[reference]->get_valid(time);
        }
    };
}