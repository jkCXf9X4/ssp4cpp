
#pragma once

#include <vector>

namespace ssp4cpp::common::list
{
    using namespace std;
    
    /**
     * @brief Check if a value exists in a container supporting begin/end.
     */
    template <typename T, typename S>
    bool is_in_list(T value, S list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }

    /**
     * @brief Helper that converts a vector of objects to a vector of pointers to those objects.
     */
    template <typename T>
    vector<T *> to_pointers(const vector<T> &v)
    {
        vector<T *> values;
        for (auto &item : v)
        {
            values.push_back(&item);
        }
        return values;
    }
}
