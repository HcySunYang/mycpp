#include <cstddef>
#include <string_view>

/*
* 1. Pass by value or const value
* 2. Pass by pointer or pointer to const or const pointer to const
* 3. Pass by reference or const reference
* 4. C style array as parameter
* 5. Default arguments
* 6. The implicit conversion of the function parameter with reference type
* 7. std::string_view as a parameter
* 8. constexpr function and consteval function
* 9. Getting things out of a function using reference parameters, or pointers
* 10. Getting things out of a function using return by value
* 11. Return by reference and return by pointer
* 12. Function return type deduction
* 13. Function overloading
* 14. Suggests the compiler to inline a function using the `inline` keyword
* 15. Function pointers
* 16. Functor or function object
*/


// =================================================================
// 1. Pass by value or const value
// =================================================================
// The parameter a is passed by value by default
// The parameter b is passed by const value
int fn1(int a, const int b);

// =================================================================
// 2. Pass by pointer or pointer to const
// =================================================================
// The parameter a is passed by pointer
// The parameter b is passed by pointer to const
// The parameter c is passed by const pointer to const
int fn2(int* a, const int* b, const int* const c);

// =================================================================
// 3. Pass by reference or const reference
// =================================================================
// The parameter a is passed by reference
// The parameter b is passed by const reference
int fn3(int& a, const int& b);

// =================================================================
// 4. C style array as parameter
// =================================================================
// The parameter a is decayed to a pointer, so the size of the array is lost, and we can't use sizeof operator or the std::size() function to get the size of the array.
// We have to receive the size of the array as a separate parameter.
int fn4(int a[], size_t count);
// If you specify the size of the array in the function parameter, it is going to be ignored.
// The size 5 of the following array is ignored.
int fn5(int a[5], size_t count);
// A reference to a sized array as a parameter
// The compiler is going to enforce that you must pass an array of the given size.
// The array parameter is not going to decay to a pointer, so you can use the sizeof operator or the std::size() function to get the size of the array.
double fn6(double (&a)[5]);
double fn7(const double (&a)[5]); // const reference to a sized array
// Milti-dimensional C style array as a parameter
// You have to specify the size of the array in all dimensions except the first dimension, otherwise you will get a compilation error.
double fn8(int a[][3][5], size_t count);
double fn9(const int a[][3][5], size_t count);  // const version
double fn10(int (&a)[4][3][5], size_t count); // The same rule as for the single-dimensional array applies here

// =================================================================
// 5. Default arguments
// =================================================================
// The default value of the parameter a is 10
// The default value can only be specified in the declaration, not in the definition.
int fn11(int a = 10);

// =================================================================
// 6. The implicit conversion of the function parameter with reference type
// =================================================================
// The parameter a is a reference to an int, but you can pass a different type of argument, for example, a double, and the compiler is going to implicitly convert it to an temporary int object:
// fn12(3.14); // The double value 3.14 is implicitly converted to an int value 3 which is an temporary int object.
// And then pass the temporary int object to the function as a reference.
int fn12(int& a) {
  a++; // It is not going to work because the a is a reference to a temporary object.
}
// We can fix it by passing the argument by const reference, since the const reference cannot be modified, we can only read the value.
int fn13(const int& a) {
  a; // It is not going to work because the a is a reference to a temporary object.
}
// This implicit conversion can explain why you can't pass a string literal to a function that expects a reference to a std::string object,
// because the string literal is a const char array, and the compiler is going to implicitly convert it to a temporary std::string object which is a temporary object.
// But we can pass the string literal to a function that expects a const reference to std::string object.

// =================================================================
// 7. std::string_view as a parameter
// =================================================================
// The std::string_view is a lightweight, non-owning, read-only view of a string.
// It is a better alternative to passing a const reference to std::string object.
// In case where you use a non-const string reference as a parameter, you cannot pass a string literal to that function,
// then you can use std::string_view as a parameter, the string view is going to accept all kinds of strings, like string literals, std::string objects, and char arrays, even std::string_view objects.
void fn14(std::string_view str);
// you can call fn14 with all kinds of strings
// fn14("Hello, World!");
// std::string str = "Hello, World!";
// fn14(str);
// char str[] = "Hello, World!";
// fn14(str);
// std::string_view str = "Hello, World!";
// fn14(str);

// =================================================================
// 8. constexpr function and consteval function
// =================================================================
// A constexpr function is a function that can potentially be evaluated at compile time,
// which means that it is possible to be evaluated at runtime.
constexpr int fn15(int a);
// when you are storing the result of a constexpr function in a variable, the能 the varable must be a constexpr so the compiler can evaluate the function at compile time.
// You can also call a constexpr function with a non-constexpr argument, then the function will be executed at runtime.

// On the other hand, C++20 introduces a new keyword consteval, which is a stronger version of constexpr.
// It forces the function to be evaluated at compile time, and if it is not possible, then the compiler is going to give you a compiler error.
consteval int fn16(int a);
// Since the consteval keyword has already conveyed that the function must be evaluated at compile time,
// you don't need to store the result of the function in a constexpr variable to make the compiler evaluate the function at compile time.

// =================================================================
// 9. Getting things out of a function using reference parameters, or pointers
// =================================================================
void fn17(
  // If the parameter is not meant to be modified, or it is only be read, then it will be better to pass it by const reference.
  const std::string& a,
  // If the parameter is not meant to be modified and it is a pointer, then it will be better to pass it by const pointer to const.
  const int* const b,
  // The output1 is what the users gets things out of the function by using non-const reference.
  int& output1,
  // The output2 is what the users gets things out of the function by using pointer.
  int* c
);

// =================================================================
// 10. Getting things out of a function using return by value
// =================================================================
// Return by value is the default way to get things out of a function.
int fn18(int a, int b) {
  return a + b;
}
// But morden C++ is going to optimeze it as much as possible when returning by value, for example:
std::string fn19(std::string str1, std::string str2) {
  auto result {str1 + str2};
  return result;
}
// Which behavior is call copy elision, refer to the chapter "Constructor - copy constructor" in language_itself/class.cpp for more details.

// =================================================================
// 11. Return by reference and return by pointer
// =================================================================
// The reference that is returned by the function most of the time is a reference to one of its parameters.
int& fn20(int& a, int& b) {
  return a > b ? a : b;
}
// If you want to store the reference returned by the function in a variable, then the variable must be a reference.
// int& ref = fn20(a, b);
// Otherwise, you will get a copy of the value that the reference is referring to.
// int value = fn20(a, b);  // value is a copy of the value that the reference is referring to.
// Don't return a reference to a local variable, because the local variable is going to be destroyed when the function returns.
int& fn21(int a, int b) {
  int c = a + b;
  return c; // The reference is referring to a local variable, which is going to be destroyed when the function returns.
}
// Return by pointer is similar to return by reference, you should not return a pointer to a local variable.
int* fn22(int a, int b) {
  int c = a + b;
  return &c; // The pointer is pointing to a local variable that is going to be destroyed when the function returns.
}

// =================================================================
// 12. Function return type deduction
// =================================================================
auto fn23() {
  // If you have multiple return statements, you must make sure that all of them return the same type.
  return 10; // The return type of the function is deduced to int
}
// Deduce a reference type
auto& fn24(int& a) {
  return a; // The return type of the function is deduced to int&
}
// You should use another reference variable to store the reference returned by the function.
// int& ref = fn24(a);
// Otherwise, you will get a copy of the value that the reference is referring to.
// int value = fn24(a);  // value is a copy of the value that the reference is referring to.
// Deduce a const reference type
const auto& fn25(int& a) {
  return a; // The return type of the function is deduced to const int&
}
// Deduce a pointer type
auto* fn26(int* a) {
  return a; // The return type of the function is deduced to int*
}
// Deduce a const pointer to const
const auto* const fn27(int* a) {
  return a; // The return type of the function is deduced to const int* const
}

// =================================================================
// 13. Function overloading
// =================================================================
// Function overloading is a feature that allows you to define multiple functions with the same name but with different parameters.
// The compiler is going to choose the right function to call based on the arguments you pass to the function.
// Function overloading with parameters:
int fn28(int a) {
  return a;
}
// The const keyword is not considered as a different parameter type,
// so the following function is going to cause a compilation error because the function is already defined.
// int fn28(const int a) {
//   return a;
// }
int fn28(double a) { // The function is overloaded with a different parameter type
  return a;
}
int fn28(int a, double b) { // The function is overloaded with a different number of parameters
  return a + b;
}
int fn28(double a, int b) { // The function is overloaded with a different order of parameters
  return a + b;
}
// Function overloading with pointers:
int fn29(int* a) {
  return *a;
}
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
// Function overloading with references:
int fn30(int& a);
int fn30(const int& a); // The function is overloaded with a const reference
int fn30(int&& a); // The function is overloaded with an rvalue reference

// =================================================================
// 14. Suggests the compiler to inline a function using the `inline` keyword
// =================================================================
inline int fn31(int a) {
  return a;
}
// Note that the `inline` keyword is just a suggestion to the compiler to inline the function,
// the compiler is not forced to inline the function, it is up to the compiler to decide whether to inline the function or not.
// Inline a function might cause the binary size to increase, because the function is going to be copied to every place where the function is called.

// =================================================================
// 15. Function pointers
// =================================================================
void some_fn(int a) {
  // Do something
}

void (*ptr_to_some_fn) (int) { some_fn }; // The function pointer is pointing to the function some_fn
auto ptr_to_some_fn2 {some_fn}; // The same as the above, but uses the auto keyword to deduce the function pointer type

// =================================================================
// 16. Functor or function object
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