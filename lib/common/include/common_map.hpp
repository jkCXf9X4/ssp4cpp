
#pragma once

#include <map>
#include <memory>
#include <vector>

namespace ssp4cpp::common::map_ns
{
    /**
     * @brief Extract the values of a map into a new vector.
     */
    template <typename K, typename V>
    std::vector<V> map_to_value_vector_copy(const std::map<K, V> &m)
    {
        std::vector<V> values;
        values.reserve(m.size());
        for (auto &[key, value] : m)
        {
            values.push_back(value);
        }
        return values;
    }

    /**
     * @brief Convert a map of std::unique_ptr values to a map of raw pointers.
     */
    template <typename K, typename V>
    std::map<K,V*> map_unique_to_ref(const std::map<K, std::unique_ptr<V>> &m)
    {
        std::map<K,V*> items;
        for (auto &[key, value] : m)
        {
            items[key] = value.get();
        }
        return items;
    }
}
