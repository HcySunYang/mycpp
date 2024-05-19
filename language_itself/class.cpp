#include <iostream>

/**
 * 1. Basic class syntax (with members, public and private access specifiers)
 * 2. Access levels work on per-class basis, not per-object basis
 * 3. member initializer list
 * 4. Constructor - default constructor
*/

// =================================================================
// 1. Basic class syntax (with members, public and private access specifiers)
// =================================================================
class MyClass {
  // default access specifier is private, so the members below are private,
  // which means that they are not accessible from outside the class
  int myInt{};
  double myDouble{};

  // Use public keyword to make the members accessible from outside the class
  public:
    int int_a{100};

  // we can change it back to private
  // private members make the class a non-aggregate type, so we can't use aggregate initialization to initialize the class
  // MyClass myCls{10, 3.14}; // error will raise
  private:
    double double_b{3.14};

    auto get_value() {
      return double_b;
    }
};
// Create an instance of the class
MyClass myClass;

// =================================================================
// 2. Access levels work on per-class basis, not per-object basis
// =================================================================
class MyClass1 {
  public:
    void print(const MyClass1& myCls) {
      // We can access the private member b of the object myCls
      std::cout << myCls.b << std::endl;
    }
  private:
    int b{20};
};
// Create an instance of the class
MyClass1 myClass1;

// =================================================================
// 3. member initializer list
// =================================================================
class MyClass2 {
  public:
    // The member initializer list is placed after the constructor's parameter list but before the constructor's body.
    MyClass2(int val) : a(val), b(3.14) {
      // The member variable a is initialized to val
    }

    int a{1};  // default initialized to 1, but the member initializer will take precedence
    double b{10.3}; // default initialized to 10, but the member initializer will take precedence
    std::string c{"Hello"}; // default initialized to "Hello"
    bool c; // uninitialized
};
// The order of the initializer in the member initializer list is matter,
// C++ compiler initialize the members in the order they are declared in the class,
// not in the order they are listed in the member initializer list.
// It is best practice to list the members in the member initializer list in the same order they are declared in the class,
// otherwise you may run into issues especially if the members depend on each other.

// =================================================================
// 4. Constructor - default constructor
// =================================================================
class MyClass3 {
  public:
    // Default constructor
    MyClass3() {
      std::cout << "Default constructor" << std::endl;
    }

    // If all of the parameters of a constructor have default value, then it becomes a default constructor,
    // we can't have more than one default constructor at the same time
    // MyClass3(int val = 1): a(val) {
    //   std::cout << "Constructor with value: " << val << std::endl;
    // }

    // If we don't provide any constructor for the class, the compiler will generate a default constructor for us,
    // the generated default constructor will be a constructor with no parameters, no member initializer list, and an empty body:
    // MyClass3(){}

    // If we provide a non-default constructor, the compiler will not generate a default constructor for us,
    // but we can tell the compiler to generate one for us:
    // MyClass3() = default;

  private:
    int a{10};
};
void test() {
  MyClass3 myCls3; // Default constructor
}