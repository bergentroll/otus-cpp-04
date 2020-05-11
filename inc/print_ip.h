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
  //auto size { t.size() };
  //for (size_t i { }; i < t.size(); i++) {
  //  std::cout << t[i];
  //  if (i < size - 1) std::cout << '.';
  //}
  std::cout << std::endl;
}

template <typename T>
void print_ip(T const &t) {
  std::cerr << "Unable to print type " << typeid(t).name() << std::endl;
}

template <typename T, typename Alloc>
void print_ip(std::vector<T, Alloc> const &t) {
  print_container(t);
}

template <typename T, typename Alloc>
void print_ip(std::list<T, Alloc> const &t) {
  print_container(t);
}

//template <typename T, typename Alloc>
//void print_ip(std::list<T, Alloc> const &t) {
//  print_container(t);
//}

void print_ip(std::string s) {
  std::cout << s << std::endl;
}

#endif
