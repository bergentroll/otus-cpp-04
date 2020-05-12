#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <sstream>

#include "print_ip.h"

using namespace std;

TEST(print_ip, string) {
  stringstream ss { };

  print_ip(string(""), ss);
  EXPECT_EQ(ss.str(), "\n");
  ss.str("");

  print_ip(string("Hello, World of Pain!"), ss);
  EXPECT_EQ(ss.str(), "Hello, World of Pain!\n");
  ss.str("");
}

TEST(print_ip, char_array) {
  stringstream ss { };

  print_ip("", ss);
  EXPECT_EQ(ss.str(), "\n");
  ss.str("");

  print_ip("Hello, World of Pain!", ss);
  EXPECT_EQ(ss.str(), "Hello, World of Pain!\n");
  ss.str("");
}

TEST(print_ip, numeric) {
  stringstream ss { };

  print_ip(uint8_t(-1), ss);
  EXPECT_EQ(ss.str(), "255\n");
  ss.str("");

  print_ip(uint32_t(1234), ss);
  EXPECT_EQ(ss.str(), "0.0.4.210\n");
  ss.str("");

  print_ip(uint64_t(8875824491850138409), ss);
  EXPECT_EQ(ss.str(), "123.45.67.89.101.112.131.41\n");
  ss.str("");
}

TEST(print_ip, containers) {
  stringstream ss { };

  print_ip(vector<int>({1, 2, 3, 4}), ss);
  EXPECT_EQ(ss.str(), "1.2.3.4\n");
  ss.str("");

  print_ip(vector<char>({1, 2, 3, 4}), ss);
  EXPECT_EQ(ss.str(), "1.2.3.4\n");
  ss.str("");

  print_ip(vector<string>({
    "The rice is cooked",
    "my milking done",
    "I live with my people",
    "along the banks of the Mahi;"}), ss);
  EXPECT_EQ(
    ss.str(),
    "The rice is cooked."
      "my milking done."
      "I live with my people."
      "along the banks of the Mahi;\n");
  ss.str("");

  print_ip(vector<bool>({true, false}), ss);
  EXPECT_EQ(ss.str(), "1.0\n");
  ss.str("");

  print_ip(list<int>({1, 2, 3, 4}), ss);
  EXPECT_EQ(ss.str(), "1.2.3.4\n");
  ss.str("");

  print_ip(list<char>({1, 2, 3, 4}), ss);
  EXPECT_EQ(ss.str(), "1.2.3.4\n");
  ss.str("");

  print_ip(list<string>({
    "The rice is cooked",
    "my milking done",
    "I live with my people",
    "along the banks of the Mahi;"}), ss);
  EXPECT_EQ(
    ss.str(),
    "The rice is cooked."
      "my milking done."
      "I live with my people."
      "along the banks of the Mahi;\n");
  ss.str("");

  print_ip(list<bool>({true, false}), ss);
  EXPECT_EQ(ss.str(), "1.0\n");
  ss.str("");
}

TEST(print_ip, tuple) {
  stringstream ss { };

  print_ip(tuple<int, int, int>({255, 255, 255}), ss);
  EXPECT_EQ(ss.str(), "255.255.255\n");
  ss.str("");

  print_ip(tuple<string, string, string, string, string>({
    "This", "is", "awesome", "overload", "ever"}), ss);
  EXPECT_EQ(ss.str(), "This.is.awesome.overload.ever\n");
  ss.str("");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
