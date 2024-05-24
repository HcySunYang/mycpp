#include <iostream>

/**
 * 1. Introduction to Value Categories
 * 2. Lvalue
 * 3. Rvalue
 * 4. A rule of thumb for identifying Lvalues and Rvalues
 * 5. Lvalue reference and Lvalue reference to const
 * 6. Rvalue reference and Rvalue reference to const
*/

// =================================================================
// 1. Introduction to Value Categories
// =================================================================
// A expression in C++ has two properties:
// 1. Type
// 2. Value Category
// Value category of an expression tells us how the expression is used in the program.
// There are six value categories in C++:
// 1. Lvalue
// 2. Rvalue
// 3. Xvalue
// 4. Prvalue
// 5. Glvalue

// =================================================================
// 2. Lvalue
// =================================================================
// Lvalue is a value category that represents an identitable memory location or object, which means that lvalues have an address.
// There are two types of lvalues:
// 1. Modifiable lvalue
// 2. Non-modifiable lvalue 
// lvalue to rvalue conversion: the lvalue will implicitly convert to an rvalue in contexts where an rvalue is expected.

// =================================================================
// 3. Rvalue
// =================================================================
// Rvalue is a value category that represents a temporary object or a value that is not identitable.
// Such as literals, a function call that returns by value, or a temporary object created by the compiler.
// Rvalues do not have an address, which means that we cannot take the address of an rvalue.

// =================================================================
// 4. A rule of thumb for identifying Lvalues and Rvalues
// =================================================================
// If you can take the address of an expression, then it is an lvalue.
// Lvalue expressions are those that evaluate to variables or other identifiable objects that persist beyond the end of the expression.
// Rvalue expressions are those that evaluate to literals or values returned by functions/operators that are discarded at the end of the expression.

// =================================================================
// 5. Lvalue reference and Lvalue reference to const
// =================================================================
// Lvalue reference is a reference that is bound to an lvalue, and a lvalue reference to const is a reference that is bound to a const lvalue.
// The Lvalue reference:
// 1. can only be initialized with a modifiable lvalue.
// 2. can be used to modify the object it refers to.
// 3. cannot be bound to an rvalue or a non-modifiable lvalue.
// The Lvalue reference to const:
// 1. can be initialized with a modifiable lvalue, a non-modifiable lvalue, or an rvalue.
// 2. cannot be used to modify the object it refers to.

// =================================================================
// 6. Rvalue reference and Rvalue reference to const
// =================================================================
// Rvalue reference is designed to be initialized with an rvalue(only), it con't be bound to an lvalue.
void test_rvalue_reference() {
  // Rvalue reference:
  int&& x{100};
  // Rvalue reference to const:
  const int&& x{100};
}
// Rvalue reference has 2 useful features:
// 1. it can entends the lifetime of a temporary object to the lifetime of the reference. (Lvalue reference to const can do this too, because it can be bound to an rvalue.)
// 2. it can be used to modify the temporary object it refers to.
// Rvalue reference is most often used as a function parameter type, which is especially useful in move semantics or if you want to have different behavior for lvalues and rvalues with the function overloading.
class Foo {
  public:
    void print(int& x) {
      std::cout << "lvalue reference: " << x << std::endl;
    }
    void print(int&& x) {
      std::cout << "rvalue reference: " << x << std::endl;
    }
};
void test_foo() {
  Foo foo;
  int x{100};
  foo.print(x); // lvalue reference
  foo.print(100); // rvalue reference
}
// Note that a rvalue reference variable itself is a lvalue.