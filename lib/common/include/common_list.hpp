
#pragma once

#include "common_interface.hpp"
#include "common_string.hpp"

#include <initializer_list>
#include <vector>

#include <concepts>
#include <optional>
#include <algorithm>


namespace ssp4cpp::common::list
{
    template <typename T, typename S>
    bool is_in_list(T value, S list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }

    template <typename T>
    class XmlNodeList : public ssp4cpp::common::interfaces::IList
    {
    public:

        std::string to_string() const
        {
            return ssp4cpp::common::str::to_str<T>(list);
        }

        void from_string(const std::string &str, const char del)
        {
            list = ssp4cpp::common::str::from_strs<T>(str, del);
        }

        void from_string(const std::string &str)
        {
            list = ssp4cpp::common::str::from_strs<T>(str);
        }
        std::vector<T> list;
    };

    // some primitive variants to be used

    class IntXmlList : public XmlNodeList<int>
    {
    };

    class UIntXmlList : public XmlNodeList<unsigned int>
    {
    };

    class DoubleXmlList : public XmlNodeList<double>
    {
    };

    class BoolXmlList : public XmlNodeList<bool>
    {
    };

    class StringXmlList : public XmlNodeList<std::string>
    {
    };
}
