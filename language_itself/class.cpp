#include <iostream>
#include <initializer_list>

#include "class.h"

/**
 * 1. Basic class syntax (with members, public and private access specifiers)
 * 2. Access levels work on per-class basis, not per-object basis
 * 3. member initializer list
 * 4. Constructor - default constructor
 * 5. Constructor - parameterized constructor and constructor delegation
 * 6. Constructor - copy constructor
 * 7. Constructor - conversion constructor and explicit keyword
 * 8. Constructor - move constructor
 * 9. Destructor
 * 10. Header and source files for class
 * 11. Nested types
 * 12. Static members
 * 13. Friend functions
 * 14. Friend classes
 * 15. Support for initializer list
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
    // Why? the following is the reason:
    // The default copy constructor generated by the compiler does a memberwise copy or shallow copy of the object,
    // which is fine if the object doesn't contain any dynamically allocated memory, but if the object contains a pointer to dynamically allocated memory,
    // we have to provide our own copy constructor, copy assignment operator, and destructor to do a deep copy of the object and to release the memory properly.

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
// 8. Constructor - move constructor
// =================================================================
template<typename T>
class MoveDemo {
  public:
    MoveDemo(T* data_): data(data_) {}

    // It is sometimes desirable to avoid the copy for a move-able object.
    MoveDemo(const MoveDemo& other) = delete;
    MoveDemo& operator=(const MoveDemo& other) = delete;

    // Move constructor
    MoveDemo(MoveDemo&& other) noexcept : data(other.data) {
      other.data = nullptr;
    }

    // Move assignment operator
    MoveDemo& operator=(MoveDemo&& other) noexcept {
      if (this == &other) {
        return *this;
      }

      // release any resource we are holding
      delete data;
      // transfer the ownership of the resource
      data = other.data;
      other.data = nullptr;

      return *this;
    }

    ~MoveDemo() {
      delete data;
    }
  private:
    T* data;
};
// When the move constructor is called:
// When the move constructor and move assignment operator are defined, and the argument for the construction and assignment is an rvalue,
// most typically a temporary object or a literal.
// At the opposize, the copy constructor and copy assignment operator will be called:
// The argument is an Lvalue, or an rvalue but the move constructor and move assignment operator are not defined.

// Aotumatic Lvalue returned by value may be moved instead of copied. (or we can say: An automatic objects returned from a function by value can be moved even if they are Lvalues).
MoveDemo<int> createDemo() {
  MoveDemo<int> res {new int{10}};
  // The res is an automatic object, it is returned by value, so even if it is an Lvalue, it can be moved instead of copied.
  // But don't forget that the compiler could do copy elision, so the move constructor may not be called at all.
  return res;
}

// We can delete the move constructor and move assignment operator to prevent the object from being moved, the syntax is the same as the copy constructor and copy assignment operator.
// But if we do that, the object may not be copable either in case where the copy elision is not applied.

// The five rules of thumb says that one of the copy constructor, copy assignment operator, move constructor, and move assignment operator, destructor is defined or deleted, then all of them should be defined or deleted.

// std::move() can be used in cases where we want to treat an Lvalue as an Rvalue for the purpose of invoking the move constructor or move assignment operator instead of the copy constructor or copy assignment operator.

// =================================================================
// 9. Destructor
// =================================================================
class MyClass8 {
 public:
  // Destructor can call other member functions as the object is still alive when the destructor is called.
  // If you don't define a destructor, the compiler will generate a default destructor for you, which an empty body.
  // The static member variables will not be destroyed by the destructor.
  // If you use std::exit() to terminate the program, the destructors will not be called.
  ~MyClass8() {
    std::cout << "Destructor" << std::endl;
  }
};

// =================================================================
// 10. Header and source files for class
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

// =================================================================
// 11. Nested types
// =================================================================
class MyClass10 {
 public:
  using NestedType = int;
  typedef int NestedTypedef;

  // Nested enum
  enum NestedEnum {
    A,
    B,
    C
  };

  // Nested class
  // Nested class can't access the this pointer of the outer class, because the nested class can be instantiated independently of the outer class,
  // but it can access the private members of the outer class
  class NestedClass {
   public:
    void print(const MyClass10& myCls10) {
      // We can access the private member a of the object myCls10
      std::cout << myCls10.a << std::endl;
    }
  };

  MyClass10(NestedType val): a(val) {}
 private:
  NestedType a{};
};
// access the nested type
MyClass10::NestedType myNestedType{10};
MyClass10::NestedTypedef myNestedTypedef{20};
// access the nested enum
MyClass10::NestedEnum myNestedEnum{MyClass10::A};
// access the nested class
void test5() {
  MyClass10 myCls10{30};
  MyClass10::NestedClass myNestedClass;
  myNestedClass.print(myCls10);
}

// =================================================================
// 12. Static members
// =================================================================
class MyClass11 {
  public:
    // In fact, the static member variable is just a global variable that lives inside the scope of the class,
    // if we define the static member variable in the class definition, it is just a declaration, not a definition,
    // so we need to define the static member variable outside the class definition
    static int count;
    // we can initialize the static member variable in the class definition, but it have to be a const integral type
    static const int age{23};
    // or inlined initialization
    static inline std::string name{"hcy"};
    // or constexpr
    // The best practice is to use the inline keyword and the constexpr specifier to define the static member variable in the class definition
    static constexpr int age3{200};

    // static member function
    static void print() {
      std::cout << "Static member function" << std::endl;
    }
    // we can also define the static member function outside the class definition
    static void print_2();
};
// define the static member variable outside the class definition,
// we can also initialize a private static member variable.
// Note that the following definition need to go in a source file, not in a header file,
// otherwise, you will get a linker error saying that the static member variable is defined multiple times if you include the header file in multiple source files,
// or we can use the inline keyword to make it inlined so it will not violate the ODR rule
int MyClass11::count{100};

// define the static member function outside the class definition, no need to use the static keyword here,
// but one thing thaht is worth noting is that the static member function defined outside the class definition is not inlined by default,
// so in order to avoid violating the ODR rule, we should either define it in the source file or use the inline keyword to make it inlined
void MyClass11::print_2() {
  std::cout << "Static member function 2" << std::endl;
}

// Static members are shared among all instances of the class
void test6() {
  // The recommended way to access a static member variable is to use the class name with the scope resolution operator
  MyClass11::count = 10;
  MyClass11 myCls11;
  // but we can also access it using the object anyway
  std::cout << myCls11.count << std::endl; // 10
  MyClass11 myCls12;
  std::cout << myCls12.count << std::endl; // 10
  // We can call the static member function using the class name with the scope resolution operator
  MyClass11::print();
}

// =================================================================
// 13. Friend functions
// =================================================================
class MyClass13;  // The forward declaration is needed
class MyClass12 {
  private:
    int a{10};
    // The friend function can access the private members of the class
    friend void print(const MyClass12& myCls12, const MyClass13& myCls13);  // friend function declaration
};
class MyClass13 {
  private:
    int a{10};
    // The friend function can access the private members of the class
    friend void print(const MyClass12& myCls12, const MyClass13& myCls13);  // friend function declaration
};
// a function can be a friend of multiple classes
void print(const MyClass12& myCls12, const MyClass13& myCls13) {
  std::cout << myCls12.a << "----" << myCls13.a << std::endl;
}

// =================================================================
// 14. Friend classes
// =================================================================
class Boy {
  public:
    Boy(int val) : age(val) {}
  private:
    int age{10};
    // It serves both as a friend declaration and a class declaration
    friend class Girl;
};

class Girl {
  public:
    void printBoy(const Boy& boy) {
      // We can access the private member of Boy
      std::cout << boy.age << std::endl;
    }
};

// We can also make a single member function a friend of another class,
// The key is to see how it works in the following example, notice that how do we arrange the forward declaration
// and the implementation of the friend function and the class.
// But if we put these 2 classes in different files, and separate the declaration and definition, then we don't
// have to worry about the order of these 2 classes, just need to include the header file of the class that is needed.
class Apple;
class Banana {
  public:
    void printApple(const Apple& apple);
};
class Apple {
  public:
    Apple(int val) : price(val) {}
  private:
    int price{10};
    friend void Banana::printApple(const Apple& apple);
};

void Banana::printApple(const Apple& apple) {
  // We can access the private member of Apple
  std::cout << apple.price << std::endl;
}

// =================================================================
// 15. Support for initializer list
// =================================================================
class YourClass {
  public:
    YourClass(size_t length) : len(length), a(new int[length]) {}

    // If you provide an initializer list constructor, then it would be better to provide a initializer list assignment operator as well,
    // and delete the copy constructor and copy assignment operator to prevent the object from being shallow copied.
    YourClass(const YourClass& other) = delete;
    YourClass& operator=(const YourClass& other) = delete;

    // The initializer list constructor
    YourClass(std::initializer_list<int> list): YourClass(list.size()) {
      size_t i = 0;
      for (auto& elem : list) {
        a[i++] = elem;
      }
    }

    // The initializer list assignment operator
    YourClass& operator=(std::initializer_list<int> list) {
      if (list.size() != len) {
        delete[] a;
        a = new int[list.size()];
        len = list.size();
      }
      size_t i = 0;
      for (auto& elem : list) {
        a[i++] = elem;
      }
      return *this;
    }

    ~YourClass() {
      delete[] a;
    }
  private:
    int* a;
    size_t len;
};

void test7() {
  // Will create an array of 5 elements
  YourClass yourCls(5);
  // Will create an array of 1 element that is 10
  YourClass yourCls2{10};
}