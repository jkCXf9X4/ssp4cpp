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

namespace ssp4cpp::str
{
    using namespace std;

    inline std::string to_string(const std::string &obj)
    {
        return obj;
    }

    inline std::string to_string(const vector<std::string> &obj)
    {
        std::string result = "{\n";
        for (const auto &item : obj)
        {
            result += item + "\n";
        }
        result += "}\n";
        return result;
    }

    inline std::string to_string(const bool &obj)
    {
        return obj ? "true" : "false";
    }

    inline std::string to_string(const int &obj)
    {
        return std::to_string(obj);
    }

    inline std::string to_string(const unsigned int &obj)
    {
        return std::to_string(obj);
    }

    inline std::string to_string(const double &obj)
    {
        return std::to_string(obj);
    }
}
