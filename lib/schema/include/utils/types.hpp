#pragma once

#include <initializer_list>
#include <vector>

#include <concepts>
#include <optional>
#include <algorithm>

namespace ssp4cpp::common::types
{
    /** @brief Helper trait to detect std::optional. */
    template <typename>
    constexpr bool is_optional_impl = false;
    template <typename T>
    constexpr bool is_optional_impl<std::optional<T>> = true;
    template <>
    inline constexpr bool is_optional_impl<std::nullopt_t> = true;

    template <typename T>
    constexpr bool is_optional_v = is_optional_impl<std::decay_t<T>>;

    /** @brief Trait to detect std::vector types. */
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

    /** @brief Concept matching any std::optional type. */
    template <typename T>
    concept any_optional = std::same_as<T, std::optional<typename T::value_type>>;

    /** @brief Concept matching any std::vector type. */
    template <typename T>
    concept any_vector = std::same_as<T, std::vector<typename T::value_type>>;
}
