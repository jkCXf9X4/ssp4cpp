

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
        common::Logger log = common::Logger("DataHandler", common::LogLevel::ext_trace);

        size_t buffer_size;
        uint64_t reference_counter;

        std::condition_variable event;
        unique_ptr<DataRecorder> recorder;
        std::vector<unique_ptr<DataBuffer>> buffers;

        DataHandler() = delete;

        DataHandler(size_t buffer_size, const std::string &filename)
        {
            log.ext_trace("[{}] Constructor", __func__);
            reference_counter = 0;
            this->buffer_size = buffer_size;
            
            recorder = make_unique<DataRecorder>(&event, filename);
        }

        // Return the reference to the data
        /** Allocate a new buffer for objects of type @p type */
        uint64_t initData(DataType type)
        {
            log.ext_trace("[{}] type init ", __func__);
            return initData(make_unique<DataBuffer>(buffer_size, 0, type));
        }

        /** Allocate a new buffer for objects of size @p obj_size and return its reference id. */
        uint64_t initData(size_t size)
        {
            log.ext_trace("[{}] size init ", __func__);
            return initData(make_unique<DataBuffer>(buffer_size, size, DataType::UNKNOWN));
        }

        uint64_t initData(std::unique_ptr<ssp4cpp::sim::handler::DataBuffer> &&buffer)
        {
            buffers.emplace_back(std::move(buffer));
            auto ref = reference_counter++;

            recorder->register_buffer(buffer.get(), ref);

            return ref;
        }

        /** Push a new sample into the buffer identified by @p reference. */
        void setData(uint64_t time, uint64_t reference, void *data)
        {
            log.ext_trace("[{}] init", __func__);
            buffers[reference]->push(data, time);
            event.notify_all();
        }

        /** Retrieve the latest valid sample from a buffer. */
        void *getData(uint64_t time, uint64_t reference)
        {
            log.ext_trace("[{}] init", __func__);
            return buffers[reference]->get_valid(time);
        }
    };
}