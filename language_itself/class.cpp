#include <iostream>

/**
 * 1. Basic class syntax (with members, public and private access specifiers)
 * 2. Access levels work on per-class basis, not per-object basis
 * 3. Constructor - basic syntax
 * 4. Constructor - member initializer list
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
// 3. Constructor - basic syntax
// =================================================================
class MyClass2 {
  public:
    // We can have multiple constructors so long as they have different parameters
    MyClass2() {
      // The downside of this approach is that the member variable a would be updated twice,
      // once in the uniform initialization list which is going to initialize the member variable a to 0,
      // and then in the body of the constructor which is going to update the member variable a to 10.
      a = 10;
    }

    MyClass2(int val) {
      // The same downside as the reason explained above
      a = val;
    }

    // This is going to initialize the member variable a to 0
    int a{};
};
// Create an instance of the class
MyClass2 myClass2;
MyClass2 myClass2_2(20);

// =================================================================
// 4. Constructor - member initializer list
// =================================================================
class MyClass3 {
  public:
    // The member initializer list is placed after the constructor's parameter list but before the constructor's body.
    MyClass3(int val) : a(val), b(3.14) {
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