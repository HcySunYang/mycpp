#include <iostream>
#include <optional>
#include <string>
#include <cstring>
#include <concepts>

template <typename T>
class Base {
  public:
    void interface() {
      // call the derived class' implementation
      static_cast<T*>(this)->implementation();
    }
    void implementation() {
      std::cout << "Base implementation" << std::endl;
    }
};

class Derived : public Base<Derived> {
  public:
};

void test2() {
  Derived d;
  d.interface();
}

int main() {
  test2();
  return 0;
}