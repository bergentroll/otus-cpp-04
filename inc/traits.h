#ifndef TRAITS_H
#define TRAITS_H

#include <type_traits>

/// @privatesection @{

/** @brief Compile-time function to check can be instance iterated.
 *
 *  Overload for not matched args.
 *  @param T Type to test.
 *  @return false.
 */
template <typename T, typename = void>
struct is_iterable: std::false_type { };

/** @brief Compile-time function to check can be instance iterated.
 *
 *  Functon matches for T::begin() and T::end() methods which is mandatory for
 *  range-based for loop.
 *  @param T Type to test.
 *  @return true.
 */
template <typename T>
struct is_iterable<
  T,
  std::void_t<
    typename T::iterator,
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end())
    >>: public std::true_type {};

/* @brief Alias for is_iterable<T>::value.
 *
 * @param T Type to test.
 */
template <typename T>
constexpr bool is_iterable_v { is_iterable<T>::value };

// Attribution to https://stackoverflow.com/a/11251408/7486328.
/** @brief Compile-time function to check whether one type is a specialisation
 * of another.
 * 
 * Overload for not matched args.
 * @param T Type to compare with.
 * @param Any type.
 * @return false.
 */
template <template <typename ...> class T, typename = void>
struct is_specialisation_of: std::false_type { };

/** @brief Compile-time function to check whether one type is a specialisation
 * of another.
 * 
 * Usage example:
 * @code
 * static_assert(is_specialisation_of<std::tuple, T>::value, true);
 * @endcode
 * @param T Type to compare with.
 * @param U Type to compare for.
 * @return false.
 */
template <template <typename ...> class T, typename ... Args>
struct is_specialisation_of<T, T<Args...>>: std::true_type { };

/* @brief Alias for is_specialisation_of<T>::value.
 *
 * @param T Type to compare with.
 * @param U Type to compare for.
 */
template <template <typename ...> class T, typename U>
constexpr bool is_specialisation_of_v { is_specialisation_of<T, U>::value };

/// @}

#endif
