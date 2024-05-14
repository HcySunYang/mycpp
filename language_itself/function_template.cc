#include <cstring>

/*
* 1. Basic syntax of a function template
* 2. Multiple type parameters
* 3. References and pointers in function templates
* 4. Non-template parameters
* 5. Include template into multiple files
* 6. Abbreviated function templates with 'auto'
* 7. Template specialization
* 8. decltype and trailing return type
* 9. decltype(auto) and the difference between auto and decltype(auto)
*/

// =================================================================
// 1. Basic syntax of a function template
// =================================================================
template <typename T>
T multiply(T a, T b) {
  return a * b;
}
// The function template can be called with any type that supports the '*' operator,
// if you call it with a type that doesn't support the '*' operator, you will get a compilation error
// multiply(1, 2); // OK, returns 3
// multiply("Hello, ", "World!"); // Error, the operator '*' is not defined for the type 'const char *'
// We can also call the function template with a type that is explicitly specified
// multiply<double>(1, 2); // OK, returns 2.0

// =================================================================
// 2. Multiple type parameters
// =================================================================
// A single one type parameter is only for one type, you can't use it for multiple types
// If you want to use multiple types, you have to use multiple type parameters
template <typename R, typename T, typename U>
R add(T a, U b) {
  return a + b;
}
// In fact, this can be simplified by using the 'auto' keyword, see the section "abbreviated function templates with 'auto'" below

// =================================================================
// 3. References and pointers in function templates
// =================================================================
// References are also supported in function templates
template <typename T>
T& max(T& a, T& b) {
  return a > b ? a : b;
}
// Pointers with template
template <typename T>
T* max(T* a, T* b) {
  return *a < *b ? a : b;
}

// =================================================================
// 4. Non-template parameters
// =================================================================
// Non-template parameters are just like normal function parameters
template<typename T>
T add(T a, T b, int c) {
  return a + b + c;
}
// The parameter 'c' is a non-template parameter

// =================================================================
// 5. Include template into multiple files
// =================================================================
// If you want to use a function template in multiple files, you have to declare and define the function template in a header file
// and include the header file in the source files that use the function template.
// The templates are exempt from the one-definition rule.
// The instances of a template is potentially inlined, and the inline function is also exempt from the ODR,
// which is why the instances of a template will not volate the one-definition rule, see ord.cpp for more information about the ODR
// But in fact, you can use decaltype to make it possible to sparate the declaration and definition of the template,
// see the section "decltype and trailing return type" below.

// =================================================================
// 6. abbreviated function templates with 'auto'
// =================================================================
auto my_fn(auto a, auto b) {
  return a + b;
}
// It is basically a shorthand for the template below,
// since the auto keyword for each parameter is a independent type:
template <typename T, typename U>
auto my_fn(T a, U b) {
  return a + b;
}
// Here we use the auto keyword to deduce the return type, the deduction rule is that the largest type will be deduced,
// the largest type is the type involved in the return statement that can hold the return value

// =================================================================
// 7. Template specialization
// =================================================================
// Template specialization is a feature that allows you to provide a different implementation for a specific template,
// The syntax is similar to the function template, but you have to specify the type that you want to specialize
template<>
char* add(char* a, const char* b) {
  return std::strcat(a, b);
}

// =================================================================
// 8. decltype and trailing return type
// =================================================================
// The decltype keyword is used to deduce the type of an expression at compile time
// The trailing return type is a syntax that allows you to specify the return type of a function after the parameter list
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
  return a + b;
}
// One benefit of using the trailing return type is that we can split the template into two parts,
// the first part is the template declaration, and the second part is the template definition,
// this is useful when the template is too long and you want to separate the declaration and definition
template<typename T, typename U>
auto add2(T a, U b) -> decltype(a + b);
// The definition of the template is in another file as follows:
template<typename T, typename U>
auto add2(T a, U b) -> decltype(a + b) {
  return a + b;
}

// =================================================================
// 9. decltype(auto) and the difference between auto and decltype(auto)
// =================================================================
template<typename T, typename U>
decltype(auto) add3(T a, U b) {
  return a + b;
}
// The difference between auto and decltype(auto) is:
// auto potentially drops the cv-qualifiers and references, while decltype(auto) preserves them:
// https://stackoverflow.com/questions/21369113/what-is-the-difference-between-auto-and-decltypeauto-when-returning-from-a-fun
// from The answer that comes from the link above, one interesting explanation is:
// The auto returns what value-type would be deduced of you assigned the return clause to an auto variable,
// while the decltype(auto) returns what type you would get if you wrap the return clause in the decltype.

