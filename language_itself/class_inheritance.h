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
 * 9. virtual destructors
 * 10. Pure virtual functions
 * 11. Virtual base classes
 * 12. Object slicing
 * 13. Dynamic cast
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
// What is CRTP? In short, CRTP is when a class A has a base class which is a template specialization of the class A itself.
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

// =================================================================
// 9. virtual destructors
// =================================================================
class BaseCls4 {
  public:
    // We should always make the destructor of the base class virtual if the class is intended to be used as a base class.
    // If we don't make the destructor virtual, the derived class' destructor will not be called when the derived class is destructed through a pointer to the base class.
    virtual ~BaseCls4() {
      std::cout << "BaseCls4 destructor" << std::endl;
    }
};

class DerivedCls5 : public BaseCls4 {
  public:
    // We don't have to mark it as virtual explicitly,
    // because if the base class' member function is virtual, the derived class' member function is virtual as well,
    // regardless of whether we mark it as virtual or not.
    ~DerivedCls5() = default;
};

// =================================================================
// 10. Pure virtual functions
// =================================================================
class BaseCls5 {
  public:
    // If a class has a pure virtual function, it is called an abstract class, which means that it can't be instantiated,
    // and it is meant to be used as a base class.
    // The derived class must override the pure virtual function, otherwise, the derived class is also an abstract class.
    virtual void implementation() = 0;
};
// We can have a definition for the pure virtual function in the base class.
void BaseCls5::implementation() {
  std::cout << "BaseCls5 implementation" << std::endl;
}

class DerivedCls6 : public BaseCls5 {
  public:
    // If we don't override the pure virtual function, the derived class is also an abstract class.
    void implementation() override {
      // We can call the base class' implementation of the pure virtual function.
      BaseCls5::implementation();
      std::cout << "DerivedCls6 implementation" << std::endl;
    }
};

// =================================================================
// 11. Virtual base classes
// =================================================================
// To fix the diamond problem, we can use virtual inheritance.
class BaseCls6 {
  public:
    int id_;
    BaseCls6(int id): id_(id) {}
};

// The DerivedCls7 and DerivedCls8 classes inherit from the BaseCls6 class virtually.
class DerivedCls7 : virtual public BaseCls6 {
  public:
    DerivedCls7(int id): BaseCls6(id) {}
};

class DerivedCls8 : virtual public BaseCls6 {
  public:
    DerivedCls8(int id): BaseCls6(id) {}
};

// The DerivedCls9 class inherits from the DerivedCls7 and DerivedCls8 classes.
// The most-derived class is responsible for constructing the virtual base class.
// The virtual base class is constructed only once, in the normal inheritance, the base class is constructed multiple times.
class DerivedCls9 : public DerivedCls7, public DerivedCls8 {
  public:
    DerivedCls9(int id): BaseCls6(id), DerivedCls7(id), DerivedCls8(id) {}
};

// =================================================================
// 12. Object slicing
// =================================================================
// Assigning a derived class object to a base class object will slice the derived class object, this process is called object slicing.
void test4() {
  DerivedCls9 d(100);
  BaseCls6 b {d}; // object slicing: only the base part of the derived class object is copied to the base class object, the derived part is sliced off.
}

// =================================================================
// 13. Dynamic cast
// =================================================================
// The dynamic_cast can be used to cast a base class pointer to a derived class pointer, which is also called downcasting.
// If the cast is successful, the dynamic_cast returns a pointer to the derived class, otherwise, it returns a nullptr.
class BaseFoo {
  public:
    virtual ~BaseFoo() {}
};

class DerivedFoo : public BaseFoo {
  public:
    virtual ~DerivedFoo() {}
    void print() {
      std::cout << "DerivedFoo" << std::endl;
    }
};

void test5() {
  BaseFoo* b = new DerivedFoo();
  DerivedFoo* d = dynamic_cast<DerivedFoo*>(b);
  if (d) {
    d->print();
  }
}
// static_cast can also be used for downcasting, but it doesn't check whether the cast is valid or not. So it is more dangerous than dynamic_cast.
// static_cast is faster than dynamic_cast because it doesn't do any runtime type checking, you can use it when you are sure that the cast is valid.

// dynamic_cast can also be used to cast a base class reference to a derived class reference,
// but there is no way to return a null reference, so if the cast is invalid, it throws a std::bad_cast exception.

// dynamic_cast uses the RTTI (Run-Time Type Information) to determine the type of the object at runtime,
// which incurs some performance overhead, and some compilers allow you to disable RTTI to improve performance,
// so it is needless to say if you disable RTTI, you can't use dynamic_cast.