#include <utility>
#include <string>

/*
* 1. Basic lambda syntax
* 2. Capture list
* 3. Mutable lambda
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
  // TODO: Add mutable lambda example
}