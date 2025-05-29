
#pragma once

#include <map>
#include <memory>
#include <vector>

namespace ssp4cpp::common::map_ns
{
    using namespace std;

    template <typename K, typename V>
    vector<V> map_to_value_vector_copy(const map<K, V> &m)
    {
        vector<V> values;
        values.reserve(m.size());
        for (auto &[key, value] : m)
        {
            values.push_back(value);
        }
        return values;
    }

    template <typename K, typename V>
    map<K,V*> map_unique_to_ref(const map<K, unique_ptr<V>> &m)
    {
        map<K,V*> items;
        for (auto &[key, value] : m)
        {
            items[key] = value.get();
        }
        return items;
    }
}
