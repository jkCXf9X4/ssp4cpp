#pragma once

#include "IXmlNode.hpp"

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

#include <type_traits>


namespace ssp4cpp::str
{
    using namespace interfaces;

    template <typename T>
    std::string to_str(const T &obj)
    {
        if constexpr (std::is_same_v<T, int> ||
                      std::is_same_v<T, unsigned int> ||
                      std::is_same_v<T, double>)
        {
            return std::to_string(obj);
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return obj ? "true" : "false";
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            return obj;
        }
        else if constexpr (std::is_base_of_v<IWritable, T>)
        {
            return obj.to_string();
        }
        else
        {
            throw std::runtime_error("Unable to print object");
            // ERROR
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
} // namespace ssp4cpp::str



