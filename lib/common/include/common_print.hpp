
#pragma once

#include <initializer_list>
#include <vector>

#include <concepts>
#include <optional>
#include <algorithm>


namespace ssp4cpp::common::print
{

    template <typename T, typename U>
    void print_map(map<T, U> &m)
    {
        for (auto const &x : m)
        {
            std::cout << x.first // string (key)
                      << ':'
                      << x.second // string's value
                      << std::endl;
        }
    }
    
}