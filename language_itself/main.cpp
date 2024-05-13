#include <iostream>
#include <optional>
#include <string>
#include <cstring>

template <typename T>
void print(T value) {
  std::cout << value << std::endl;
}

template <typename T>
void print(T* value, T* value2) {
  std::cout << *value << std::endl;
  std::cout << *value2 << std::endl;
  std::cout << std::strcmp(value, value2) << std::endl;
}

int main() {

  const char* str = "C";
  const char* str2 = "B";
  print(str, str2);
    
    return 0;
}