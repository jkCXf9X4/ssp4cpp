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
        uint64_t valid_input_time;

        StepData(){}

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
            os << "StepData: \n{" << std::endl
               << "start_time: " << start_time << std::endl
               << "end_time: " << end_time << std::endl
               << "timestep: " << timestep << std::endl
               << "valid_input_time: " << valid_input_time << std::endl
               << "}" << std::endl;
        }
    };

    class Invocable : public virtual common::str::IString
    {
    public:

        virtual void init() = 0;
        virtual uint64_t invoke(StepData data) = 0;

        virtual void print(std::ostream &os) const
        {
            os << "Invocable:\n{}" << std::endl;
        }
    };

    class InvocableNode : public common::graph::Node, public Invocable
    {
    public:
        virtual void print(std::ostream &os) const
        {
            os << "InvocableNode:\n{}" << std::endl;
        }
    };
}