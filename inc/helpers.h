#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <string>
#include <tuple>

/// @privatesection @{

/** @brief Wrapper function to make string.
 *
 *  Function needs to uniformely get string from various types.
 *  @param t Any object that can be converted with std::string.
 *  @return String made from arg..
 */
template <typename T>
std::string to_string(T t) {
  return std::to_string(t);
}

/** @brief Wrapper function to make string.
 *
 *  Function needs to uniformely get string from various types.
 *  @param ch Any char.
 *  @return String containing given symbol.
 */
std::string to_string(char ch) {
  return to_string(static_cast<unsigned char>(ch));
}

/** @brief Wrapper function to make string.
 *
 *  Function needs to uniformely get string from various types.
 *  @param ch C-style string.
 *  @return std::string constructed from given C-string.
 */
std::string to_string(const char *ch) {
  return std::string(ch);
}

/** @brief Wrapper function to make string.
 *
 *  Function needs to uniformely get string from various types.
 *  @param s Regular std::string.
 *  @return Copy of input string.
 */
std::string to_string(std::string const &s) {
  return s;
}

/** @brief Pretty print IP address.
 *
 *  Print pair as a dot-separated IP address.
 *  @param t Tuple of two same typed items.
 *  @param stream Output stream to push in.
 *  @throw static_assert When items of tuple is not same typed.
 */
template <typename T1, typename T2>
void print_ip_tuple_impl(std::tuple<T1, T2> const &t, std::ostream &stream = std::cout) {
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
void print_ip_tuple_impl(std::tuple<Head, Tail ...> const &t, std::ostream &stream = std::cout) {
  using Second = typename std::tuple_element<0, std::tuple<Tail ...> >::type;
  static_assert(std::is_same<Head, Second>());
  stream << to_string(std::get<0>(t)) << '.';
  std::apply(
    [&stream](auto head, auto ... tail) {
      print_ip_tuple_impl(std::make_tuple(tail...), stream);
    }, t);
}

/// @}

#endif
