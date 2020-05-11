#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

template <typename T>
void print_container(T const &t) {
  auto begin { t.cbegin() };
  auto end { t.cend() };
  for (auto it { begin }; it != end; it++) {
    if (it != begin) std::cout << '.';
    std::cout << static_cast<int>(*it);
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
    std::cout << std::to_string(static_cast<unsigned char>(bytes[i]));
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

//template <typename T, typename Alloc>
//void print_ip(std::list<T, Alloc> const &t) {
//  print_container(t);
//}

#endif
