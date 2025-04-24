
#pragma once


#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace ssp4cpp::common::log
{
    void setup_log()
    {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);

    }

    
    
}