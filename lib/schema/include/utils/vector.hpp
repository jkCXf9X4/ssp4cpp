
#pragma once

#include <vector>

namespace ssp4cpp::utils::list
{    
    /**
     * @brief Check if a value exists in a container supporting begin/end.
     */
    template <typename T, typename S>
    bool is_in_list(T value, S list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }

}
