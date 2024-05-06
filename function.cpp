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
// when you are storing the result of a constexpr function in a variable, them the varable must be a constexpr so the compiler can evaluate the function at compile time.
// You can also call a constexpr function with a non-constexpr argument, then the function will be executed at runtime.

// On the other hand, C++20 introduces a new keyword consteval, which is a stronger version of constexpr.
// It forces the function to be evaluated at compile time, and if it is not possible, then the compiler is going to give you a compiler error.
consteval int fn16(int a);
// Since the consteval keyword has already conveyed that the function must be evaluated at compile time,
// you don't need to store the result of the function in a constexpr variable to make the compiler evaluate the function at compile time.