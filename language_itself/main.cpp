#include <iostream>
#include <optional>
#include <string>
#include <cstring>
#include <concepts>

template <typename T, typename U>
struct MyStruct6 {
  T a;
  U b; // type template parameter can have a default value
  int c; // non-template type member
};

int main() {
  return 0;
}