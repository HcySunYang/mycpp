#include <string>
#include <iostream>

/**
 * 1. Basic inheritance
*/

// Samples
class SuperClass {
  public:
    int id_;

    SuperClass(int id) : id_(id) {}

    int getId() {
      return id_;
    }
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