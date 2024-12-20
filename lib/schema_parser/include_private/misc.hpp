
#include <initializer_list>
#include <vector>

#include <concepts>
#include <optional>
#include <algorithm>


namespace ssp4cpp::misc
{
    namespace types
    {
        template <typename>
        constexpr bool is_optional_impl = false;
        template <typename T>
        constexpr bool is_optional_impl<std::optional<T>> = true;
        template <>
        constexpr bool is_optional_impl<std::nullopt_t> = true;

        template <typename T>
        constexpr bool is_optional_v = is_optional_impl<std::decay_t<T>>;


        template <typename C>
        struct is_vector : std::false_type
        {
        };
        template <typename T, typename A>
        struct is_vector<std::vector<T, A>> : std::true_type
        {
        };
        template <typename C>
        inline constexpr bool is_vector_v = is_vector<C>::value;


        template <typename T>
        concept any_optional = std::same_as<T, std::optional<typename T::value_type>>;

        template <typename T>
        concept any_vector = std::same_as<T, std::vector<typename T::value_type>>;
    }

    template <typename T, typename S>
    inline bool is_in_list(T value, S list)
    {
        return std::find(list.begin(), list.end(), value) != list.end();
    }
}