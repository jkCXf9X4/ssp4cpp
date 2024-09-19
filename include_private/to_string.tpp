#pragma once

#include <string>
#include <vector>
#include <optional>

// Templates
template <typename T>
std::string to_string_optional(const std::optional<T> &opt)
{
    return opt ? to_string(opt.value()) : "null";
}

template <typename T>
std::string to_string_vector(const std::vector<T> &vec)
{
    std::string result = "{\n";
    for (const auto &item : vec)
    {
        result += to_string(item) + "\n";
    }
    result += "}\n";
    return result;
}
