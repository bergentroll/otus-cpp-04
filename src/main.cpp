#include <iostream>
#include <vector>
#include <list>
#include <tuple>

#include "print_ip.h"

int main(int argc, char **argv) {
  char ch { -1 };
  short sh { 0 };
  int i { 2130706433 };
  long l { 8875824491850138409 };
  std::string s { "127.0.0.1" };
  std::vector<int> v { 192, 168, 0, 1 };
  std::list<char> lst { 10, 8, 0, 1 };
  std::tuple<int, std::string, char, size_t> tup { 172, "16", 10, 255 };

  print_ip(ch);
  print_ip(sh);
  print_ip(i);
  print_ip(l);
  print_ip(s);
  print_ip(v);
  print_ip(lst);
  //print_ip(tup);
  return EXIT_SUCCESS;
}
