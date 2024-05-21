#include <iostream>

// This is the class definition, the compiler needs to see the full definition so it can know how much memory to allocate
class GoodClass {
  public:
    // this is the constructor declaration, its definition is in class.cpp
    GoodClass(double val);
    // for trivial functions, it is better to leave the implementation in the header file,
    // functions like this that are defined inside the class definition are implicitly inlined,
    // so they are not violating the ODR rule
    double GetB() { return b; };

    // for non-trivial functions, it is better to have their implementation in the source file
    void DoSomethingComplicated();

    void DoSomethingElse();

  private:
    double b{20.0};
};

// Member functions that are defined outside the class definition are not inlined by default,
// but we can use the inline keyword to make them inlined, then it will not violate the ODR rule,
// and can be included in multiple source files
inline void GoodClass::DoSomethingElse() {
  std::cout << "Doing something else" << std::endl;
}