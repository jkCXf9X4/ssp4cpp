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

// std::string to_string(const std::string &str) {return str;}
// std::string to_string(const int &i) {return std::to_string(i);}
// std::string to_string(const double &d) {return std::to_string(d);}
// std::string to_string(const bool &b) {return b ? "true" : "false";}
