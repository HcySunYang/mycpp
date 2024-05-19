#include <iostream>
#include <optional>
#include <string>
#include <cstring>
#include <concepts>

class MyClass3 {
  public:
    // Default constructor
    MyClass3() {
      std::cout << "Default constructor" << std::endl;
    }
    MyClass3(int val = 1): a(val) {
      std::cout << "Constructor with value: " << val << std::endl;
    }
  private:
    int a{10};
};

int main() {
  MyClass3 myCls3; // Default constructor
  return 0;
}