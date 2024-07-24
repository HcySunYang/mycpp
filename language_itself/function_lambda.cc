#include <utility>
#include <string>
#include <functional>
#include <array>

/*
* 1. Basic lambda syntax
* 2. Capture list
* 3. Mutable lambda
* 4. Functor or function object
* 5. Lambda can be passed to a function that receives a function pointer
* 6. Capturing the 'this' pointer
* 7. std::function
*/

void function_lambda() {
  // =================================================================
  // 1. Basic lambda syntax
  // =================================================================
  // The lambda syntax is as follows:
  // [capture list](parameters) -> return_type { body }
  auto lambda {[]() -> int { return 1; }}; // No capture list and no parameters, returns an integer
  lambda(); // Call the lambda function
  // A Lambda function can be self executed
  []() { return 1; }(); // Self executed lambda function
  // With parameters
  auto lambda_with_parameters {[](int a, int b) { return a + b; }};
  lambda_with_parameters(1, 2); // Call the lambda function with parameters

  // =================================================================
  // 2. Capture list
  // =================================================================
  // Capture by value
  int a {1};
  int b {2};
  auto lambda2 {[a]() { return a; }};
  // Capture by reference
  auto lambda3 {[&a]() { return a; }};
  // Capture all variables by value
  auto lambda4 {[=]() { return a; }};
  // Capture all variables by reference
  auto lambda5 {[&]() { return a; }};
  // Capture all variables by value, but capture 'a' by reference
  auto lambda6 {[=, &a]() { return a; }};
  // Capture all variables by reference, but capture 'a' by value
  auto lambda7 {[&, a]() { return a; }};
  // Capture by move
  std::string str {"Hello, World!"};
  auto lambda8 {[str = std::move(str)]() { return str; }};
  // The str is moved to the lambda, so str is empty, you can't use it anymore after the definition of lambda8
  // Capture all variables by reference, but capture 'str2' by move
  std::string str2 {"Hello, World!"};
  auto lambda9 {[&, str2 = std::move(str2)]() { return str2; }};
  // Capture all variables by value, but capture 'str3' by move
  std::string str3 {"Hello, World!"};
  auto lambda10 {[=, str3 = std::move(str3)]() { return str3; }};

  // =================================================================
  // 3. Mutable lambda
  // =================================================================
  // By default, the lambda is const, you can't modify the captured variables, if you want to modify the captured variables, you have to use the 'mutable' keyword
  auto lambda11 {[a]() mutable { return a++; }};
  // this is not a good practice, you should avoid using mutable lambda, it makes the code harder to understand as the captured variables can be modified in different calls to the lambda
  lambda11(); // Modify 'a'
  lambda11(); // Modify 'a' again
  // it introduces side effects, which is not good for the code readability and maintainability
}


// =================================================================
// 4. Functor or function object
// =================================================================
// A functor is a class that overloads the function call operator `operator()`.
class Decryptor {
  public:
    std::string operator()(std::string str) {
      // Decrypt the string
      return str;
    }
};
// You can call the functor like a function
void test_functor() {
  Decryptor decryptor;
  std::string decrypted_str = decryptor("Encrypted string");
}
// Also check out the build in function object in the header file <functional>:
// https://en.cppreference.com/w/cpp/utility/functional

// since functor is just a class, it can contain member variables, and you can initialize the member variables in the constructor.
class Encryptor {
  public:
    Encryptor(const std::string key) : key_{key} {}
    std::string operator()(std::string str) {
      // Encrypt the string
      return str + key_;
    }
  private:
    std::string key_;
};
void test_functor2() {
  Encryptor encryptor {"key"};
  std::string encrypted_str = encryptor("String to encrypt");
}

// Note that the Lambda is actually modeled behind the scene as a functor or function object

// =================================================================
// 5. Lambda can be passed to a function that receives a function pointer
// =================================================================
void function_that_receives_function_pointer(int (*func)(int, int)) {
  func(1, 2);
}
void test_lambda_as_function_pointer() {
  function_that_receives_function_pointer([](int a, int b) { return a + b; });
}

// =================================================================
// 6. Capturing the 'this' pointer
// =================================================================
class MyClass {
  public:
    void test() {
      // Capture the 'this' pointer
      auto lambda {[this]() { return a; }};
      lambda();
    }
  private:
    int a {1};
};

// =================================================================
// 7. std::function
// =================================================================
// std::function is a wrapper around a function pointer, a functor, or a lambda
// It can be used to store a function pointer, a functor, or a lambda in a variable
// https://en.cppreference.com/w/cpp/utility/functional/function
int add(int a, int b) {
  return a + b;
}
class Adder {
  public:
    int operator()(int a, int b) {
      return a + b;
    }
};
void test_std_function() {
  std::array<std::function<int(int, int)>, 3> functions;
  // store a function pointer
  functions[0] = add;
  // store a functor
  Adder adder;
  functions[1] = adder;
  // store a lambda
  functions[2] = [](int a, int b) { return a + b; };
}