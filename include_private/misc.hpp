
#include <initializer_list>
#include <vector>


namespace ssp4cpp::misc
{
    template <typename T>
    inline bool is_in_list(T value, std::initializer_list<T> list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }

    template <typename T>
    inline bool is_in_list(T value, std::vector<T> list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }
}