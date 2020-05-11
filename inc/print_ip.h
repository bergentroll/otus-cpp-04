#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

/// @todo Use everywhere.
std::string to_string(std::string const &s) {
  return s;
}

template <typename T>
std::string to_string(T t) {
  return std::to_string(t);
}

std::string to_string(char ch) {
  return to_string(static_cast<unsigned char>(ch));
}

std::string to_string(const char *ch) {
  return std::string(ch);
}

template <typename T>
void print_container(T const &t) {
  auto begin { t.cbegin() };
  auto end { t.cend() };
  for (auto it { begin }; it != end; it++) {
    if (it != begin) std::cout << '.';
    std::cout << to_string(*it);
  }
  std::cout << std::endl;
}

template <typename T>
void print_ip(T t) {
  constexpr size_t type_size { sizeof(T) };

  union {
    unsigned char bytes[type_size];
    T value;
  };

  value = t;

  for (int i { type_size - 1 }; i >= 0; i--) {
    std::cout << to_string(bytes[i]);
    if (i != 0) std::cout << '.';
  }
  std::cout << std::endl;
}

template <typename T, typename Alloc>
void print_ip(std::vector<T, Alloc> const &t) {
  print_container(t);
}

template <typename T, typename Alloc>
void print_ip(std::list<T, Alloc> const &t) {
  print_container(t);
}

void print_ip(std::string s) {
  std::cout << s << std::endl;
}

template <typename T>
void print_ip(std::tuple<T> const &t) {
  std::cout << to_string(std::get<0>(t)) << std::endl;
}

template <typename Head, typename ... Tail>
void print_ip(std::tuple<Head, Tail ...> const &t) {
  static_assert(std::is_same<Head, typename std::tuple_element<0, std::tuple<Tail ...> >::type>());
  std::cout << to_string(std::get<0>(t)) << '.';
  std::apply(
    [](auto head, auto ... tail) {
      print_ip(std::make_tuple(tail...));
    }, t);
}

#endif
