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
  std::string s { "localhost" };
  std::vector<int> v { 192, 168, 0, 1 };
  std::list<char> lst { 10, 8, 0, 1 };
  std::tuple<size_t, size_t, size_t, size_t> tup_i { 172, 16, 10, 255 };
  std::tuple<
    std::string,
    std::string,
    std::string,
    std::string> tup_s { "45", "12", "19", "27" };

  print_ip(ch);
  print_ip(sh);
  print_ip(i);
  print_ip(l);
  print_ip(s);
  print_ip(v);
  print_ip(lst);
  print_ip(tup_i);
  print_ip(tup_s);

  return EXIT_SUCCESS;
}
