#pragma once

#include "data_type.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::utils
{

    constexpr handler::DataType get_variable_type(fmi4cpp::fmi2::scalar_variable var)
    {

        if (var.is_boolean())
        {
            return handler::DataType::boolean;
        }
        else if (var.is_enumeration())
        {
            return handler::DataType::enumeration;
        }
        else if (var.is_integer())
        {
            return handler::DataType::integer;
        }
        else if (var.is_real())
        {
            return handler::DataType::real;
        }
        else if (var.is_string())
        {
            return handler::DataType::string;
        }
        else
        {
            throw runtime_error("Unknown type");
        }
    }
}