#include <tuple>

#include "print_ip.h"

int main(int argc, char** argv) {
  #if defined TEST1
    print_ip(std::tuple<int, int, char>(1, 2, 3));
  #elif defined TEST2
    print_ip(std::tuple<int, char>(1, 2));
  #endif
  return EXIT_SUCCESS;
}
