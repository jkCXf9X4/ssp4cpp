
#pragma once

#include "common_interface.hpp"
#include "common_string.hpp"

#include <initializer_list>
#include <vector>
#include <concepts>
#include <optional>
#include <algorithm>
#include <map>

namespace ssp4cpp::common::list
{
    using namespace std;
    template <typename T, typename S>
    bool is_in_list(T value, S list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }

    template <typename K, typename V>
    vector<V> map_to_value_vector(const map<K,V> &m)
    {
        vector<V> values;
        values.reserve(m.size());
        for (auto &&[key, value]: m)
        {
            values.push_back(value);
        }
        return values;
    }

    template <typename K, typename V>
    map<K,V> map_from_pairs(const vector<pair<K,V>> &v)
    {
        map<K, V> result;
        for (auto &[key, values] : v)
        {
            result[key] = values;
        }
        return result;
    }


    template <typename T>
    vector<T*> to_pointers(const vector<T> &v)
    {
        vector<T*> values;
        for (auto &item: v)
        {
            values.push_back(&item);
        }
        return values;
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
