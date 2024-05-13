
/*
* 1. Basic syntax of a function template
* 2. Multiple type parameters
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
// We can also call the function template with a type that is not explicitly specified
// multiply<double>(1, 2); // OK, returns 2.0

// =================================================================
// 2. Multiple type parameters
// =================================================================
// A single one type parameter is only for one type, you can't use it for multiple types
// If you want to use multiple types, you have to use multiple type parameters
template <typename T1, typename T2>
T1 add(T1 a, T2 b) {
  return a + b;
}