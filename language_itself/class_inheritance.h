#include <string>
#include <iostream>

/**
 * 1. Basic inheritance
 * 2. Inheritance access specifiers
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