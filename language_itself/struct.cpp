#include <iostream>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// All the introduction to struct are also applicable to class, except that struct members are public by default, while class members are private by default.
// Most of the time, we use structs as an aggregate type so they don't have constructors, destructors that will be used in classes.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * 1. Struct - and aggregate initialization
 * 2. Struct - and designated initializers (C++20)
 * 3. Struct - assignment with aggregate initialization and designated initializers
 * 4. Struct - default member initialization
 * 5. Struct - nested struct
 * 6. Struct template
 * 7. Struct - member functions
 * 8. const struct object
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
// 3. Struct - assignment with aggregate assignment and designated assignment
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

// =================================================================
// 4. Struct - default member initialization
// =================================================================
struct MyStruct5 {
  int a;  // uninitialized
  double b{}; // value-initialized, initialized to 0.0
  int c{10}; // default member initialization, initialized to 10 if not provided
};
MyStruct5 myStruct5; // .a = uninitialized, .b = 0.0, .c = 10
MyStruct5 myStruct5_2{1, 2.3, 4}; // .a = 1, .b = 2.3, .c = 4, explicit initialization value takes precedence over default member initialization

// =================================================================
// 5. Struct - nested struct
// =================================================================
// First, we can use another struct type (or program-defined type) as a member of a struct
struct Employee {
  int age{};
  double salary{};
};
struct Company {
  int employee_count{};
  Employee CEO{}; // nested struct
};
Company myCompany{10, {50, 100000.0}}; // .employee_count = 10, .CEO.age = 50, .CEO.salary = 100000.0

// Second, we can define a struct inside another struct
struct Company2 {
  struct Employee2 {
    int age{};
    double salary{};
  };
  int employee_count{};
  Employee2 CEO{};
};
Company2 myCompany2{10, {50, 100000.0}}; // .employee_count = 10, .CEO.age = 50, .CEO.salary = 100000.0

// =================================================================
// 6. Struct template
// =================================================================
template <typename T, typename U>
struct MyStruct6 {
  T a;
  U b = double; // type template parameter can have a default value
  int c; // non-template type member
};
MyStruct6<int, double> myStruct6{10, 3.14, 100};
// template struct as a parameter
template <typename T, typename U>
void print_struct(const MyStruct6<T, U>& myStruct) {
  std::cout << myStruct.a << ", " << myStruct.b << ", " << myStruct.c << std::endl;
}
void wrapper_fn2() {
  print_struct(myStruct6);
}

// =================================================================
// 7. Struct - member functions
// =================================================================
struct MyStruct7 {
  int a;
  double b;
  // Member functions are implicitly inlined so they are won't volatile the ODR rule
  void print() {
    std::cout << a << ", " << b << std::endl;
  }
  // Member function can be overloaded
  void print(int x) {
    std::cout << a << ", " << b << ", " << x << std::endl;
  }
};

// =================================================================
// 8. const struct object
// =================================================================
struct MyStruct8 {
  int a;
  void print() {
    std::cout << a << std::endl;
  }
  void print() const { // const-qualified member function, it is treated as an overload
    std::cout << a << std::endl;
  }
  void print(int x) const {
    std::cout << a << ", " << x << std::endl;
  }
};
const MyStruct8 myStruct8{10}; // the member a is const-qualified, so it cannot be modified
// myStruct8.a = 20; // error will raise
// myStruct8.print(); // error will raise, because the member function print is not const-qualified
void wrapper_fn3() {
  myStruct8.print(); // this will call the const-qualified member function print
}
// const member function can be called on non-const object
MyStruct8 myStruct8_2{20};
void wrapper_fn4() {
  myStruct8_2.print(3); // will call the const-qualified member function print(int x)
}
// Since the const member function call be called on both the const and non-const object,
// if a member function does not modify the object, it is best to make it const-qualified.