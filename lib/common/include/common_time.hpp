
#pragma once

#include "common_interface.hpp"
#include "common_string.hpp"



namespace ssp4cpp::common::time
{
    int constexpr milliseconds_per_seconds  = 1000;
    int constexpr microseconds_per_seconds  = 1000000;
    int constexpr nanoseconds_per_seconds  =  1000000000;
    
    int constexpr seconds_per_hour =  3600;
    int constexpr hours_per_day = 24;
}
