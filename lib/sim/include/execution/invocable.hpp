#pragma once

#include "common_string.hpp"
#include "common_node.hpp"

#include <cstdint>
#include <string>

namespace ssp4cpp::sim::graph
{

    class StepData : public common::str::IString
    {
    public:
        uint64_t start_time;
        uint64_t end_time;
        uint64_t timestep;
        bool include_valid_input_time = false;
        uint64_t valid_input_time = 0;

        StepData() {}

        StepData(uint64_t start_time,
                 uint64_t end_time,
                 uint64_t timestep,
                 uint64_t valid_input_time)
        {
            this->start_time = start_time;
            this->end_time = end_time;
            this->timestep = timestep;
            this->valid_input_time = valid_input_time;
            include_valid_input_time = true;
        }

        StepData(uint64_t start_time,
                 uint64_t end_time,
                 uint64_t timestep)
        {
            this->start_time = start_time;
            this->end_time = end_time;
            this->timestep = timestep;
            include_valid_input_time = false;
        }

        virtual void print(std::ostream &os) const
        {
            os << "StepData: \n{"
               << " start_time: " << start_time
               << " end_time: " << end_time
               << " timestep: " << timestep;
            if (include_valid_input_time)
            {
                os << " valid_input_time: " << valid_input_time;
            }
            os << " }\n";
        }
    };

    class Invocable : public common::graph::Node, public virtual common::str::IString
    {
    public:
        uint64_t walltime_ns = 0;
        uint64_t id = 0;

        virtual void init() = 0;
        virtual uint64_t invoke(StepData data, const bool only_feedthrough = false) = 0;

        virtual void print(std::ostream &os) const
        {
            os << "Invocable:\n{}\n";
        }
    };
}