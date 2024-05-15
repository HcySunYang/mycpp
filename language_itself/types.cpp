#include <concepts>

/*
* 1. Type aliases
* 2. decltype
* 3. type traits: https://en.cppreference.com/w/cpp/header/type_traits
* 4. Conditional compilation with type traits and if constexpr
* 5. Concepts (since C++20) - with the requires clause
* 6. Concepts - use concept directly in the template parameter list
* 7. Concepts - use concept with auto
*/

// =================================================================
// 1. Type aliases
// =================================================================
// Type aliases are a way to create a new name for an existing type.
using byte = unsigned char;
// The old way to create a type alias is to use typedef
typedef unsigned char byte2;  // Not recommended

// =================================================================
// 2. decltype
// =================================================================
// The decltype keyword is used to determine the type of an expression at compile time.
// It is a bit like the typeof operator in TypeScript.
byte b {1};
using byte2 = decltype(b); // byte2 is now an alias for unsigned char
byte2 b2 {2};

// =================================================================
// 3. type traits: https://en.cppreference.com/w/cpp/header/type_traits
// =================================================================
// The type traits are a set of classes that allow you to query the properties of a type at compile time.
// For example, you can check if a type is a pointer, a reference, a class, an enum, etc.
// The type traits are defined in the <type_traits> header file.
// It is useful when you want to constrain a template type to a specific type.
template <typename T>
auto add(T a, T b) {
  static_assert(std::is_integral<T>::value, "T must be an integral type");
  // Since C++17
  // static_assert(std::is_integral_v<T>, "T must be an integral type");
  return a + b;
}

// =================================================================
// 4. Conditional compilation with type traits and if constexpr
// =================================================================
// The if constexpr statement is a new feature in C++17 that allows you to conditionally compile code based on a compile-time condition.
// It is similar to the if statement, but the condition must be a compile-time constant.
template <typename T>
auto add2(T a, T b) {
  if constexpr (std::is_integral<T>::value) {
    return a + b;
  } else {
    return 0;
  }
}

// =================================================================
// 5. Concepts (since C++20) - with the requires clause
// =================================================================
// Concepts are a new feature in C++20 that allows you to constrain template parameters to specific types.
template <typename T, typename U>
requires std::integral<T> && std::floating_point<U>
auto add3(T a, U b) {
  return a + b;
}
// We can also put the requires clause after the parameter list
template<typename T, typename U>
auto add3_2(T a, U b) requires std::integral<T> && std::floating_point<U> {
  return a + b;
}

// =================================================================
// 6. Concepts - use concept directly in the template parameter list
// =================================================================
// You can also use concepts directly in the template parameter list, without the requires clause.
template <std::integral T, std::floating_point U>
auto add4(T a, U b) {
  return a + b;
}

// =================================================================
// 7. Concepts - use concept with auto
// =================================================================
// You can also use concepts with the auto keyword to deduce the type of a variable.
auto add5(std::integral auto a, std::floating_point auto b) {
  return a + b;
}