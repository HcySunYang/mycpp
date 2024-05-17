
/**
 * 1. Basic class syntax (with members, public and private access specifiers)
 * 2. Constructor part 1
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
  private:
    double double_b{3.14};

    auto get_value() {
      return double_b;
    }
};
// Create an instance of the class
MyClass myClass;

// =================================================================
// 2. Constructor part 1
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
