#pragma once

#include "common_interface.hpp"

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <sstream>
#include <map>

#include <type_traits>

// dont name this 'string', to many collisions
namespace ssp4cpp::common::str
{
    using namespace interfaces;

    /**
     * @brief Convert various primitive types and custom objects implementing
     *        IWritable to their string representation.
     */
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
        }
    }

    /**
     * @brief Convert a map to a multi-line string listing key/value pairs.
     */
    template <typename T, typename U>
    std::string to_str(const std::map<T, U> &obj)
    {
        std::stringstream ss;
        ss << "Map [key:value]" << std::endl;
        // key : value
        for (auto const [key, value] : obj)
        {
            ss << key << ':' << value << std::endl;
        }
        return ss.str();
    }

    /**
     * @brief Convert an optional value to string, returning "null" when empty.
     */
    template <typename T>
    std::string to_str(const std::optional<T> &obj)
    {
        return obj ? to_str(obj.value()) : "null";
    }

    /**
     * @brief Convert a vector of values to a newline separated list inside braces.
     */
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

    /**
     * @brief Use operator<< to convert an object to string via a stringstream.
     */
    template <typename T>
    std::string stream_to_str(const T &obj)
    {
        std::stringstream ss;
        ss << obj;
        return ss.str();
    }

    /**
     * @brief Parse a string into the requested type.
     */
    template <typename T>
    T from_str(const std::string &str)
    {
        if constexpr (std::is_same_v<T, int>)
        {
            return std::stoi(str);
        }
        else if constexpr (std::is_same_v<T, unsigned int>)
        {
            return std::stoul(str);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return std::stod(str);
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return str == "true";
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            return str;
        }
        else if constexpr (std::is_base_of_v<IReadable, T>)
        {
            T item;
            item.from_string(str);
            return item;
        }
        else
        {
            throw std::runtime_error("Unsupported type");
        }
    }

    /**
     * @brief Split a delimited string and convert each token to type T.
     */
    template <typename T>
    std::vector<T> from_strs(const std::string &str, const char del)
    {
        auto list = std::vector<T>();

        std::istringstream ss;
        ss.str(str);

        for (std::string word; std::getline(ss, word, del);)
        {
            T item = from_str<T>(word);

            list.push_back(item);
        }
        return list;
    }

    /**
     * @brief Convenience overload using space as delimiter.
     */
    template <typename T>
    std::vector<T> from_strs(const std::string &str)
    {
        return from_strs<T>(str, ' ');
    }

} // namespace ssp4cpp::str
