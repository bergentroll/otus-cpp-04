#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <iostream>
#include <list>
#include <tuple>
#include <type_traits>
#include <vector>

/** @brief Wrapper function to make string.
 *  Function needs to uniformely get string from various types.
 *  @param t Any object that can be converted with std::string.
 *  @return String made from arg..
 */
template <typename T>
std::string to_string(T t) {
  return std::to_string(t);
}

/** @brief Wrapper function to make string.
 *  Function needs to uniformely get string from various types.
 *  @param ch Any char.
 *  @return String containing given symbol.
 */
std::string to_string(char ch) {
  return to_string(static_cast<unsigned char>(ch));
}

/** @brief Wrapper function to make string.
 *  Function needs to uniformely get string from various types.
 *  @param ch C-style string.
 *  @return std::string constructed from given C-string.
 */
std::string to_string(const char *ch) {
  return std::string(ch);
}

/** @brief Wrapper function to make string.
 *  Function needs to uniformely get string from various types.
 *  @param s Regular std::string.
 *  @return Copy of input string.
 */
std::string to_string(std::string const &s) {
  return s;
}

/// @todo
template <typename T, typename = void>
struct is_iterable: std::false_type {};

/// @todo
template <typename T>
struct is_iterable<
  T,
  std::void_t<
    typename T::iterator,
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end())
    >>: public std::true_type {};

template <typename T>
constexpr bool is_iterable_v { is_iterable<T>::value };

/** @brief Pretty print IP address.
 *  Overload print integer-valued data as a dot-separated IP address. Octets is
 *  bytes of given value.
 *  @param t Integer-valued data.
 *  @param stream Output stream to push in.
 */
template <
  typename T,
  std::enable_if_t<std::is_integral_v<T>, int> = 0>
void print_ip(T t, std::ostream &stream = std::cout) {
  constexpr size_t type_size { sizeof(T) };

  union {
    unsigned char bytes[type_size];
    T value;
  };

  value = t;

  for (int i { type_size - 1 }; i >= 0; i--) {
    stream << to_string(bytes[i]);
    if (i != 0) stream << '.';
  }
  stream << std::endl;
}

/** @brief Pretty print IP address.
 *  Print STL-style container as a dot-separated IP address. Every item is an
 *  octet.
 *  @param Container STL-style container taken items type and allocator type as
 *  first two template parameters. Items can have primitive numeric, C-style or
 *  std::string type.
 *  @param stream Output stream to push in.
 */
template <
  typename T,
  std::enable_if_t<
    is_iterable_v<T> && !std::is_same_v<T, std::string>,
    int> = 0>
void print_ip(T const &t, std::ostream &stream = std::cout) {
  auto begin { t.cbegin() };
  auto end { t.cend() };
  for (auto it { begin }; it != end; it++) {
    if (it != begin) stream << '.';
    stream << to_string(*it);
  }
  stream << std::endl;
}

/** @brief Pretty print IP address.
 *  Print pair as a dot-separated IP address.
 *  @param t Tuple of two same typed items.
 *  @param stream Output stream to push in.
 *  @throw static_assert When items of tuple is not same typed.
 */
template <typename T1, typename T2>
void print_ip(std::tuple<T1, T2> const &t, std::ostream &stream = std::cout) {
  static_assert(std::is_same<T1, T2>());
  stream
    << to_string(std::get<0>(t)) << '.'
    << to_string(std::get<1>(t)) << std::endl;
}

/** @brief Pretty print IP address.
 *  Print tuple as a dot-separated IP address.
 *  @param t Tuple of same typed items.
 *  @param stream Output stream to push in.
 *  @throw static_assert When items of tuple is not same typed.
 */
template <typename Head, typename ... Tail>
void print_ip(std::tuple<Head, Tail ...> const &t, std::ostream &stream = std::cout) {
  using Second = typename std::tuple_element<0, std::tuple<Tail ...> >::type;
  static_assert(std::is_same<Head, Second>());
  stream << to_string(std::get<0>(t)) << '.';
  std::apply(
    [&stream](auto head, auto ... tail) {
      print_ip(std::make_tuple(tail...), stream);
    }, t);
}

/** @brief Pretty print IP address.
 *  Print string as is.
 *  @param s std::string to be printed.
 *  @param stream Output stream to push in.
 */
template <
  typename T,
  std::enable_if_t<std::is_same_v<T, std::string>, int> = 0>
void print_ip(T t, std::ostream &stream = std::cout) {
  stream << t << std::endl;
}

/** @brief Pretty print IP address.
 *  Print string as is.
 *  @param ch C-style string to be printed.
 *  @param stream Output stream to push in.
 */
template <
  typename T,
  std::enable_if_t<std::is_same_v<T, const char*>, int> = 0>
void print_ip(T t, std::ostream &stream = std::cout) {
  stream << t << std::endl;
}

#endif
