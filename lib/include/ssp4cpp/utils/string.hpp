#pragma once

#include "ssp4cpp/utils/interface.hpp"

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <sstream>
#include <map>
#include <concepts>
#include <format>

#include <type_traits>

// dont name this 'string', to many collisions
namespace ssp4cpp::utils::str
{
    using namespace interfaces;

    template <class T>
    concept Ostreamable = requires(std::ostream &os, const T &t) {
        { os << t } -> std::same_as<std::ostream &>;
    };

    template <class T>
    concept HasToString = requires(const T &t) {
        { t.to_string() } -> std::convertible_to<std::string>;
    };

    template <class>
    inline constexpr bool dependent_false_v = false;

    template <typename T>
    std::string to_string(T &&obj)
    {
        using U = std::remove_cvref_t<T>;

        if constexpr (std::same_as<U, bool>)
        {
            return obj ? "true" : "false";
        }
        else if constexpr (std::same_as<U, std::string>)
        {
            return obj;
        }
        else if constexpr (std::same_as<U, std::string_view>)
        {
            return std::string(obj);
        }
        else if constexpr (std::is_same_v<U, const char *> || std::is_same_v<U, char *>)
        {
            return obj ? std::string(obj) : std::string{};
        }
        else if constexpr (std::is_enum_v<U>)
        {
            return std::to_string(static_cast<std::underlying_type_t<U>>(obj));
        }
        else if constexpr (std::is_arithmetic_v<U>)
        {
            return std::format("{}", obj);
        }
        else if constexpr (HasToString<U>)
        {
            return obj.to_string();
        }
        else if constexpr (Ostreamable<U>)
        {
            std::ostringstream oss;
            oss << obj;
            return oss.str();
        }
        else
        {
            static_assert(dependent_false_v<U>,
                          "to_string(): Unsupported type. Add to_string() or operator<<.");
        }
    }

    /**
     * @brief Convert an optional value to string, returning "null" when empty.
     */
    template <typename T>
    std::string to_string(const std::optional<T> &obj)
    {
        return obj ? to_string(obj.value()) : "null";
    }

    /**
     * @brief Convert a map to a multi-line string listing key/value pairs.
     */
    template <typename T, typename U>
    std::string to_string(const std::map<T, U> &obj)
    {
        std::string out;
        out.reserve(64);

        out += "Map [key:value]\n";
        // key : value
        for (const auto &[key, value] : obj)
        {
            out += to_string(key) + ':' + to_string(value) + '\n';
        }
        return out;
    }

    /**
     * @brief Convert a vector of values to a newline separated list inside braces.
     */
    template <typename T>
    std::string to_string(const std::vector<T> &obj)
    {
        std::string result = "{\n";
        for (const auto &item : obj)
        {
            result += to_string(item) + "\n";
        }
        result += "}\n";
        return result;
    }

    /**
     * @brief Split a delimited string into a string list.
     */
    inline std::vector<std::string> split_string(std::string_view str,
                                                 std::string_view delim)
    {
        std::vector<std::string> result;

        if (delim.empty())
        {
            result.emplace_back(str);
            return result;
        }

        size_t start = 0;
        while (true)
        {
            size_t pos = str.find(delim, start);
            if (pos == std::string_view::npos)
            {
                result.emplace_back(str.substr(start));
                break;
            }
            result.emplace_back(str.substr(start, pos - start));
            start = pos + delim.size();
        }

        return result;
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
    std::vector<T> from_strs(const std::string &str, const std::string &del)
    {
        std::vector<T> result;

        for (auto &word : split_string(str, del))
        {
            if (word != "")
            {
                T item = from_str<T>(word);
                result.emplace_back(std::move(item));
            }
        }
        return result;
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
