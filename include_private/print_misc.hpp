#pragma once

#include <string>
#include <vector>
#include <optional>


// Templates
template <typename T>
std::string to_string_optional(const std::optional<T> &opt)
{
    if (opt)
    {
        return to_string(opt.value());
    }
    else
    {
        return "null";
    }
}