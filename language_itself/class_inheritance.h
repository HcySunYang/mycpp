#include <string>
#include <iostream>

/**
 * 1. Basic inheritance
 * 2. Inheritance access specifiers
 * 3. final inheritance
 * 4. Changing an inherited member's access specifier
 * 5. Curiously Recurring Template Pattern (CRTP): https://en.cppreference.com/w/cpp/language/crtp
 * 6. Virtual functions - virtual keyword
 * 7. Virtual functions - override specifier and final specifier
 * 8. virtual functions - covariant return types
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

// ================================================================
// 3. Final inheritance
// ================================================================
class BaseA {};
class DerivedA final: public BaseA {};
// class DerivedB: public DerivedA {};  // error: the DerivedA class is marked as final

// =================================================================
// 4. Changing an inherited member's access level
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
// 5. Curiously Recurring Template Pattern (CRTP): https://en.cppreference.com/w/cpp/language/crtp
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

// =================================================================
// 6. Virtual functions - virtual keyword
// =================================================================
class BaseCls {
  public:
    BaseCls() {
      // Don't call virtual function in constructor or destructor
      // 1. If you call a virtual function in a constructor, the derived class have not been constructed yet, the virtual function will be resolved to the base class' implementation.
      // 2. If you call a virtual function in a destructor, the derived class have been destructed, the virtual function will be resolved to the base class' implementation.
    }
    ~BaseCls() {
      // Don't call virtual function in constructor or destructor, the same reason as above.
    }
    virtual void implementation() {
      std::cout << "Base implementation" << std::endl;
    }
    virtual void implementation2() {
      std::cout << "Base implementation2" << std::endl;
    }
};

class DerivedCls : public BaseCls {
  public:
    virtual void implementation() {
      std::cout << "Derived implementation" << std::endl;
    }
    // This is valid even though there is no virtual function called `implementation100` in the base class.
    // So we don't recommend this approach, instead, we should use override keyword to make sure the function is overriding a virtual function in the base class.
    virtual void implementation100() {
      std::cout << "Derived implementation" << std::endl;
    }
};

void test3() {
  DerivedCls d;
  // The virtual function resolution is only done when that virtual function is called on a `pointer` or `reference` to the base class.
  BaseCls* b = &d;
  b->implementation();  // Derived implementation
  b->implementation2();  // Base implementation2
}

// =================================================================
// 7. Virtual functions - override specifier and final specifier
// =================================================================
class BaseCls2 {
  public:
    virtual void implementation() {
      std::cout << "Base implementation" << std::endl;
    }
    virtual void implementation2() {
      std::cout << "Base implementation2" << std::endl;
    }
};

class DerivedCls2 : public BaseCls2 {
  public:
    // The override specifier is used to make sure that the function is overriding a virtual function in the base class.
    // Otherwise, if the function is not overriding a virtual function in the base class, the compiler will give an error.
    // The rule of thumb is to use virtual keyword in the base class and override specifier in the derived class.
    // The override specifier implies that the function is virtual so we don't need to use virtual keyword again.
    void implementation() override {
      std::cout << "Derived implementation" << std::endl;
    }
    // The final specifier is used to prevent the function from being overridden in the derived class.
    void implementation2() final {
      std::cout << "Derived implementation2" << std::endl;
    }
};

class DerivedCls3 : public DerivedCls2 {
  public:
    // void implementation2() override; // error, because the function is final in the DerivedCls2 class
};

// =================================================================
// 8. virtual functions - covariant return types
// =================================================================
class BaseCls3 {
  public:
    BaseCls3(const BaseCls3& other) {}
    virtual BaseCls3* clone() {
      return new BaseCls3(*this);
    }
};

class DerivedCls4 : public BaseCls3 {
  public:
    DerivedCls4(const DerivedCls4& other) : BaseCls3(other) {}
    // The return type of the overridden function can be a pointer to the derived class.
    DerivedCls4* clone() override {
      return new DerivedCls4(*this);
    }
};