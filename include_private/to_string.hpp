#pragma once

#include <string>
#include <vector>
#include <optional>

#include "IXmlNode.hpp"


template <typename T>
std::string to_str(const T &obj)
{   
    if constexpr (is_same_v<T, int>)
    {
        return std::to_string(obj);
    }
    else if constexpr (is_same_v<T, unsigned int>)
    {
        return std::to_string(obj);
    }
    else if constexpr (is_same_v<T, double>)
    {
        return std::to_string(obj);
    }
    else if constexpr (is_same_v<T, bool>)
    {
        return obj ? "true" : "false";
    }
    else if constexpr (is_same_v<T, string>)
    {
        return obj;
    }
    else if constexpr (is_base_of_v<IXmlNode, T>)
    {
        return obj.to_string();
    }
    else 
    {
        //Error
        return to_string(obj);
    }
}

template <typename T>
std::string to_str(const std::optional<T> &obj)
{   
    return obj ? to_str(obj.value()) : "null";
}

template <typename T>
std::string to_str(const std::vector<T> &obj)
{   
    std::string result = "{\n";
    for (const auto &item : obj)
    {
        result += to_str(item) + "\n";
    }
    result += "}\n";
    return result;
}
