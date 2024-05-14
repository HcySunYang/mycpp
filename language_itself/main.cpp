#include <iostream>
#include <optional>
#include <string>
#include <cstring>

template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
  return a + b;
}

int main() {

    auto aaa {add(1, 2.9)}; // OK, returns 3
    using byte = unsigned char;
    byte b {1};
    using byte2 = decltype(b); // byte2 is now an alias for unsigned char
    byte2 b2 {2};
    return 0;
}