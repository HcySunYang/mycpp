#include <iostream>
#include <optional>
#include <string>
// For overloading a function with pointer types, the const keyword is considered as a different parameter type.
int fn29(const int* a) { // The function is overloaded with a const pointer
  return *a;
}
// The following function is the same as `int fn29(int* a)`
// Since regardless whether the pointer is const or not, it is just a copy of the passed pointer,
// so if the following function co-exists with `int fn29(int* a)`, then it is going to cause a compilation error.
int fn29(int* const a) {
  return *a;
}
// The following function is the same as `int fn29(const int* a)`
// Since regardless whether the pointer is const or not, it is just a copy of the passed pointer,
// so if the following function co-exists with `int fn29(const int* a)`, then it is going to cause a compilation error.
int fn29(const int* const a) {
  return *a;
}
int main() {

  std::optional<int> aaa {1};

  std::cout << "The size of the optional is " << sizeof(aaa) << " bytes\n";

  std::optional<double> bbb {1.0};

  std::cout << "The size of the optional is " << sizeof(bbb) << " bytes\n";
    
    return 0;
}