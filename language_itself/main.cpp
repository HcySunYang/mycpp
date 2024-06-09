#include <iostream>
#include <optional>
#include <string>
#include <cstring>
#include <concepts>

template <typename T, size_t size>
class BaseStaticArray {
  public:
    T& operator[](size_t index) {
      return m_array[index];
    }
  protected:
    T m_array[size] {};
};

template <size_t length>
class DerivedStaticArray : public BaseStaticArray<double, length> {
  public:
    double& operator[](size_t index) {
      return BaseStaticArray<double, length>::m_array[index];
    }
};


int main() {
  DerivedStaticArray<3> arr;
  arr[0] = 1.0;
  arr[1] = 2.0;
  arr[2] = 3.0;
  std::cout << arr[0] << std::endl;
  std::cout << arr[1] << std::endl;
  std::cout << arr[2] << std::endl;
  return 0;
}