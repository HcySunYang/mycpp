
/*
* 1. Type aliases
* 2. decltype
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