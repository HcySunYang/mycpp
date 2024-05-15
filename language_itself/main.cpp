#include <iostream>
#include <optional>
#include <string>
#include <cstring>
#include <concepts>

template <typename T, typename U>
requires std::integral<T> && std::floating_point<U>
auto add(T a, U b) {
  return a + b;
}

int main() {

    auto aaa {add(1, 2.2)}; // OK, returns 3
    std::cout << aaa << std::endl;
    return 0;
}