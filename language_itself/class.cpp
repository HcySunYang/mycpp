#include <iostream>

#include "class.h"

/**
 * 1. Basic class syntax (with members, public and private access specifiers)
 * 2. Access levels work on per-class basis, not per-object basis
 * 3. member initializer list
 * 4. Constructor - default constructor
 * 5. Constructor - parameterized constructor and constructor delegation
 * 6. Constructor - copy constructor
 * 7. Constructor - conversion constructor and explicit keyword
 * 8. Header and source files for class
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

// =================================================================
// 5. Constructor - parameterized constructor and constructor delegation
// =================================================================
class MyClass4 {
  public:
    // Parameterized constructor
    MyClass4(int val) : a(val) {
      std::cout << "Parameterized constructor" << std::endl;
    }

    // Constructor delegation, if a constructor delegates to another constructor, then the constructor can't have a member initializer list,
    // it is more common to have a constructor with fewer parameters delegate to a constructor with more parameters
    MyClass4() : MyClass4(10) {
      std::cout << "Constructor delegation" << std::endl;
    }

  private:
    int a{10};
};

// =================================================================
// 6. Constructor - copy constructor
// =================================================================
// The below class is a class that has only a default constructor
class MyClass5 {
  public:
    // Default constructor
    MyClass5(int val = 1) : a(val) {
      std::cout << "Default constructor" << std::endl;
    }

  private:
    int a{};
};
// What will be happening if we do something like this:
void test1() {
  MyClass5 myCls5{10}; // this will call the default constructor
  MyClass5 myCls6{myCls5}; // but what kind of constructor will be called here?
  // The answer is that the compiler will generate a copy constructor for us, and it will be called here
  // The generated copy constructor will do memberwise copy of the object
}
// We can define our own copy constructor
class MyClass6 {
  public:
    // Default constructor
    MyClass6(int val = 1) : a(val) {
      std::cout << "Default constructor" << std::endl;
    }

    // Copy constructor
    // The copy constructor should accept a const lvalue reference to the same type as the class itself
    // The copy constructor will be called implicitly when we pass an object by value to a function, or when we return an object by value from a function,
    // but the compiler may optimize out the copy constructor call in some cases, which is called copy elision
    MyClass6(const MyClass6& myCls6) : a(myCls6.a) {
      std::cout << "Copy constructor" << std::endl;
      // The copy constructor shouldn't do anything other than just copying, since the compiler may do a copy elision so the copy constructor will be elided
    }
    // If you want, you can tell the compiler to generate a copy constructor for you:
    // MyClass6(const MyClass6& myCls6) = default;

    // Sometimes we want to prevent our class from being copied, we can delete the copy constructor
    // MyClass6(const MyClass6& myCls6) = delete;
    // MyClass6 myCls6{myCls5}; // error will raise

    // Rule of three: If you need to define any of the following, you should define all three:
    // 1. Destructor
    // 2. Copy constructor
    // 3. Copy assignment operator
    // Which involves the rule of five: If you need to define any of the following, you should define all five:
    // 1. Destructor
    // 2. Copy constructor
    // 3. Copy assignment operator
    // 4. Move constructor
    // 5. Move assignment operator

  private:
    int a{};
};

// =================================================================
// 7. Constructor - conversion constructor and explicit keyword
// =================================================================
class MyClass7 {
 public:
  // By default, all constructors are considered to be conversion constructors
  MyClass7(double val) : a(val) {
    std::cout << "Default constructor" << std::endl;
  }

 private:
  double a{};
};
void test2() {
  // The below line will call the conversion constructor
  MyClass7 myCls7{3.14};
}

// Only one user-defined conversion function is allowed in a class
class MyClass8 {
 public:
  MyClass8(std::string val) {
    std::cout << "Conversion constructor" << std::endl;
  }
};
void printMyClass8(MyClass8 myCls8){}
void test3() {
  // The below line will raise an error, because only one user-defined conversion function is allowed in a class,
  // in the below case, the C-Style string needs to be converted to std::string first, then to MyClass8,
  // this involves two user-defined conversion functions, which is not allowed
  // printMyClass8("Hello");
  // But we can do this:
  printMyClass8(std::string("Hello"));
}

// To prevent the compiler from using a constructor for implicit conversions, we can use the explicit keyword
class MyClass9 {
 public:
  explicit MyClass9(std::string val) {
    std::cout << "Cannot be used as a conversion constructor" << std::endl;
  }
};
void printMyClass9(MyClass9 myCls9){}
void test4() {
  // The below line will raise an error, because the constructor is marked as explicit
  // printMyClass9(std::string("Hello"));
}

// =================================================================
// 8. Header and source files for class
// =================================================================
// Put the class definition in the header file
// Path: language_itself/class.h
// The implementations
GoodClass::GoodClass(double val) : b(val) {
  std::cout << "GoodClass constructor" << std::endl;
}
void GoodClass::DoSomethingComplicated() {
  std::cout << "Doing something complicated" << std::endl;
}