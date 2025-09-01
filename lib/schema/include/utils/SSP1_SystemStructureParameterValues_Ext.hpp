

#pragma once

#include "SSP1_SystemStructureParameterValues.hpp"
#include "FMI2_modelDescription.hpp"

namespace ssp4cpp::ssp1::ssv
{
    using DataType = ssp4cpp::fmi2::md::Type;

    DataType get_parameter_type(TParameter &par)
    {
        if (par.Boolean.has_value())
        {
            return DataType::boolean;
        }
        else if (par.Enumeration.has_value())
        {
            return DataType::enumeration;
        }
        else if (par.Integer.has_value())
        {
            return DataType::integer;
        }
        else if (par.Real.has_value())
        {
            return DataType::real;
        }
        else if (par.String.has_value())
        {
            return DataType::string;
        }
        else
        {
            throw runtime_error("Unknown type");
        }
    }

    void *get_parameter_value(TParameter &par)
    {
        if (par.Boolean.has_value())
        {
            return &par.Boolean.value().value;
        }
        else if (par.Enumeration.has_value())
        {
            return &par.Enumeration.value().value;
        }
        else if (par.Integer.has_value())
        {
            return &par.Integer.value().value;
        }
        else if (par.Real.has_value())
        {
            return &par.Real.value().value;
        }
        else if (par.String.has_value())
        {
            return &par.String.value().value;
        }
        return nullptr;
    }

}
