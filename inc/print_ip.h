#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include "helpers.h"
#include "traits.h"

/** @brief Pretty print IP address.
 *
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
 *
 *  Print STL-style container as a dot-separated IP address. Every item is an
 *  octet.
 *  @param t Iterable with T:begin(), T::end() container. Items can have
 *  primitive numeric, C-style or std::string type.
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
 *
 *  Print tuple as a dot-separated IP address.
 *  @param t Tuple of same typed items.
 *  @param stream Output stream to push in.
 *  @throw static_assert When items of tuple is not same typed.
 *  @todo Ref.
 *  @todo Throw.
 */
template <
  typename T,
  std::enable_if_t<is_specialisation_of_v<std::tuple, T>, int> = 0,
  typename = std::add_lvalue_reference<T>>
void print_ip(T t, std::ostream &stream = std::cout) {
  //static_assert(std::is_reference<T>());
  print_ip_tuple_impl(t, stream);
}

/** @brief Pretty print IP address.
 *
 *  Print string as is.
 *  @param t std::string to be printed.
 *  @param stream Output stream to push in.
 */
template <
  typename T,
  std::enable_if_t<std::is_same_v<T, std::string>, int> = 0>
void print_ip(T t, std::ostream &stream = std::cout) {
  stream << t << std::endl;
}

/** @brief Pretty print IP address.
 *
 *  Print string as is.
 *  @param t C-style string to be printed.
 *  @param stream Output stream to push in.
 */
template <
  typename T,
  std::enable_if_t<std::is_same_v<T, const char*>, int> = 0>
void print_ip(T t, std::ostream &stream = std::cout) {
  stream << t << std::endl;
}

#endif
