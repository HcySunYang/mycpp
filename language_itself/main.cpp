#include <iostream>
#include <optional>
#include <string>

int main() {

  int a {1};
  std::string str2 {"Hello, World!"};
  auto lambda9 {[&, str2 = std::move(str2)]() {
    a++;
    std::cout << "a: " << a << std::endl;
    return str2;
  }};
  a++;
  std::cout << lambda9() << std::endl;

  std::cout << "Finished" << std::endl;
    
    return 0;
}