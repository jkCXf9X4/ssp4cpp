#pragma once

#include "FMI2_Enums.hpp"

namespace ssp4cpp::sim
{
    using Causality = ssp4cpp::fmi2::md::Causality;
    using DataType = ssp4cpp::fmi2::md::Type;
}


// log_toggle.hpp
#ifdef _LOG_
  #define IF_LOG(stmt) do { stmt } while (0)
#else
  #define IF_LOG(stmt) do { } while (0)
#endif