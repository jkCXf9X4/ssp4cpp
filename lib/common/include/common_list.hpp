
#pragma once

#include <initializer_list>
#include <vector>

#include <concepts>
#include <optional>
#include <algorithm>


namespace ssp4cpp::common::list
{
    template <typename T, typename S>
    inline bool is_in_list(T value, S list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }
}
