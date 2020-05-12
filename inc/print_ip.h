#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

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

template <
  template<typename, typename> typename Container,
  typename T, 
  typename Alloc>
void print_ip(Container<T, Alloc> const &t, std::ostream &stream = std::cout) {
  auto begin { t.cbegin() };
  auto end { t.cend() };
  for (auto it { begin }; it != end; it++) {
    if (it != begin) stream << '.';
    stream << to_string(*it);
  }
  stream << std::endl;
}

template <typename T1, typename T2>
void print_ip(std::tuple<T1, T2> const &t, std::ostream &stream = std::cout) {
  static_assert(std::is_same<T1, T2>());
  stream
    << to_string(std::get<0>(t)) << '.'
    << to_string(std::get<1>(t)) << std::endl;
}

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

void print_ip(std::string s, std::ostream &stream = std::cout) {
  stream << s << std::endl;
}

void print_ip(char const *ch, std::ostream &stream = std::cout) {
  stream << ch << std::endl;
}

#endif
