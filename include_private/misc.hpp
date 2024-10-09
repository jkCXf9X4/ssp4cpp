
#include <initializer_list>


namespace ssp4cpp::misc
{
    template <typename T>
    inline bool enum_in_list(T value, std::initializer_list<T> list)
    {
        return std::find(list.begin(), list.end(), value) != list.end()
    }
}