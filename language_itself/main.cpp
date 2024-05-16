#include <iostream>
#include <optional>
#include <string>
#include <cstring>
#include <concepts>

template<typename T>
concept Addable3 = requires (T a) {
  a++;
  requires sizeof(T) <= 4; // This will check the value of sizeof(T) <= 4
};

auto add(Addable3 auto a, Addable3 auto b) {
  return a + b;
}

int main() {
  std::cout << add(1.3, 2.5) << std::endl;
    return 0;
}