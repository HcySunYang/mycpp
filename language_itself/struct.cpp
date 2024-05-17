
/**
 * 1. Struct - and aggregate initialization
 * 2. Struct - and designated initializers (C++20)
 * 3. Struct - assignment with aggregate initialization and designated initializers
*/

// =================================================================
// 1. Struct - and aggregate initialization
// =================================================================
// Aggregate type is a type that can be initialized with an aggregate initializer,
// refer to https://en.cppreference.com/w/cpp/language/aggregate_initialization
struct MyStruct2 {
  int a;
  double b;
};
MyStruct2 myStruct2{10, 3.14}; // the member a is initialized to 10 and the member b is initialized to 3.14, which is called memberwise initialization
MyStruct2 myStruct2_2{100}; // the member a is initialized to 100 and the member b is initialized to 0.0(which means the member b is value-initialized)
MyStruct2 myStruct2_3{}; // the members a and b are value-initialized
MyStruct2 myStruct2_4{myStruct2}; // do list initialization with another struct of the same type (this is not aggregate initialization, but we mention it here)
const MyStruct2 myStruct2_4{10, 3.14}; // the members a and b are const-qualified
constexpr MyStruct2 myStruct2_5{10, 3.14}; // the members a and b are constexpr-qualified

// =================================================================
// 2. Struct - and designated initializers (C++20)
// =================================================================
struct MyStruct3 {
  int a;
  double b;
};
MyStruct3 myStruct3{.a{10}, .b{3.12}}; // the member a is initialized to 10 and the member b is initialized to 3.14
MyStruct3 myStruct3_2{.a = 100}; // the member a is initialized to 100 and the member b is initialized to 0.0(which means the member b is value-initialized)
// MyStruct3 myStruct3_3{.b{3.14}, .a{10}}; // error will raise, because the order of the designated initializers must match the order of the members in the struct

// =================================================================
// 3. Struct - assignment with aggregate initialization and designated initializers
// =================================================================
struct MyStruct4 {
  int a;
  double b;
};
void wrapper_fn() {
  MyStruct4 myStruct4;
  myStruct4 = {10, 3.14}; // This will do memberwise assignment
  myStruct4 = {.a = 10, .b = 3.14};
  myStruct4 = {.b = 3.14}; // the member a will be assigned to 0
}