#include <string>
#include <iostream>

/**
 * 1. Basic inheritance
 * 2. Inheritance access specifiers
 * 3. Changing an inherited member's access specifier
 * 4. Curiously Recurring Template Pattern (CRTP): https://en.cppreference.com/w/cpp/language/crtp
*/

// Samples
class SuperClass {
  public:
    int id_;

    SuperClass(int id) : id_(id) {}

    int getId() {
      return id_;
    }
  protected:
    int protectedId_;
    void protectedMethod() {}
  private:
    int privateId_;
};

// =================================================================
// 1. Basic inheritance
// =================================================================
// The order of the construction of the derived class is that the most-base class is constructed first, and the most-child class is constructed last.
// The order of destruction is reversed, the most-child class is destructed first, and the most-base class is destructed last.
class SubClass : public SuperClass {
  public:
    std::string name_;
    
    SubClass(int id, const std::string& name) : SuperClass(id), name_(name) {}
};

void test() {
  SubClass sub {1, "SubClass"};
  // access the member function that is inherited from the super class
  std::cout << sub.getId() << std::endl;
}

// =================================================================
// 2. Inheritance access specifiers
// =================================================================
class A: public SuperClass {
  public:
    A(int id) : SuperClass(id) {
      // access the public and protected member of the super class
      id_ = 1;
      protectedId_ = 1;
    }
};
void test2() {
  A a {1};
  // access the public member of the super class
  std::cout << a.id_ << std::endl;
}

class B: protected SuperClass {
  public:
    B(int id) : SuperClass(id) {
      // access the public and protected member of the super class
      id_ = 1;
      protectedId_ = 1;
    }
};
void test3() {
  B b {1};
  // b.id_; // error
}

class C: private SuperClass {
  public:
    C(int id): SuperClass(id) {
      // access the public and protected member of the super class
      id_ = 1;
      protectedId_ = 1;
    }
};
void test4() {
  C c {1};
  // c.id_; // error
}

// =================================================================
// 3. Changing an inherited member's access level
// =================================================================
class D : public SuperClass {
  public:
    D(int id): SuperClass(id) {}
    // use the `using` keywork to change the access level of SuperClass::protectedMethod
    using SuperClass::protectedMethod;
    // We can use = delete to delete functionality from the base class
    int getId() = delete;
  private:
    // Hiding the functionality of the base class by changing the base class' member from public to private
    using SuperClass::id_;
};

void test() {
  D d(100);
  d.protectedMethod();  // this is accessible
  // d.getId(); // error, because it is deleted
  static_cast<SuperClass>(d).getId(); // this is still accessible
  d.SuperClass::getId(); // this is still accessible
  // d.id_; // error, because it is private now
}

// =================================================================
// 4. Curiously Recurring Template Pattern (CRTP): https://en.cppreference.com/w/cpp/language/crtp
// =================================================================
template <typename T>
class Base {
  public:
    void interface() {
      // call the derived class' implementation
      static_cast<T*>(this)->implementation();
    }
    void implementation() {
      std::cout << "Base implementation" << std::endl;
    }
};

class Derived : public Base<Derived> {
  public:
    void implementation() {
      std::cout << "Derived implementation" << std::endl;
    }
};

void test2() {
  Derived d;
  d.interface();  // Derived implementation
  // If we don't override the implementation function in the derived class, the base class' implementation function will be called, which prints "Base implementation".
}