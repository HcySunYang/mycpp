#include <iostream>
#include <optional>
#include <string>
#include <cstring>
#include <concepts>
#include <span>
#include <array>
#include <vector>

void print() {
  std::cout << "I will be called at last" << std::endl;
}

template<typename T, typename ...Args>
void print(T val, Args... args) {
  std::cout << val << std::endl;
  print(args...);
}

int main() {
  print(1, 2, 3, 4, 5);
  return 0;
}