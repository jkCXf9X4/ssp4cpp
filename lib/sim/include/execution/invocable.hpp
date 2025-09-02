#pragma once

#include "common_string.hpp"

#include <cstdint>

namespace ssp4cpp::sim::graph
{

    class Invocable :  public common::str::IString
    {
    public:
        virtual uint64_t invoke(uint64_t start_time, uint64_t end_time, uint64_t timestep) = 0;

        friend std::ostream &operator<<(std::ostream &os, const Invocable &obj)
        {
            os << "Invocable:\n{}" << std::endl;

            return os;
        }

    };
}