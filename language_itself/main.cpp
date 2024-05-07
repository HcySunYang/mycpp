#include <iostream>

std::string fn19(std::string str1, std::string str2) {
  auto result = str1 + str2;
    std::cout << &result << std::endl;
    return result;
}

int main() {
    std::string str1 {"Hello, "};
    std::string str2 {"World!"};
    std::string result = fn19(str1, str2);
    std::cout << result << std::endl;
    std::cout << &result << std::endl;
    return 0;
}