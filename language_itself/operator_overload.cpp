#include <iostream>

/**
 * 1. Operator overloading
 * 2. Overloading arithmetic operators using friend functions
 * 3. Overloading operators using normal functions
 * 4. Overloading operators using member functions
 * 5. Overloading using friend functions vs normal functions vs member functions
 * 6. Overloading typecast operators
 */

// =================================================================
// 1. Operator overloading
// =================================================================
// Operator overloading is a feature in C++ where we can define the operator's behavior for user-defined types.
// The operators are implemented as functions in C++.
// Best practices:
// - Operators that don't modify their operands should return by value.
// - Operators that modify their most-left operand should return a reference to the modified operand.

// =================================================================
// 2. Overloading arithmetic operators using friend functions
// =================================================================
class Cents {
  public:
    Cents(int cents): m_cents(cents) {}

    // The friend function can be defined inlined in the class definition
    friend Cents operator+(const Cents& c1, const Cents& c2) {
      // Add two Cents objects should not modify the operands,
      // so we should return a new Cents object
      return Cents(c1.m_cents + c2.m_cents);
    }
    // The friend function can also be defined outside the class definition
    friend Cents operator-(const Cents& c1, const Cents& c2);
    // friend Cents operator*(const Cents& c1, const Cents& c2);
    // friend Cents operator/(const Cents& c1, const Cents& c2);

    // Overloading operator+ for Cents + int and int + Cents
    friend Cents operator+(const Cents& c1, int value) {
      return Cents(c1.m_cents + value);
    }
    // Note that we implement the operator+ for int + Cents using another operator+ function that is for Cents + int
    friend Cents operator+(int value, const Cents& c1) {
      return Cents(c1.m_cents + value);
    }
  private:
    int m_cents;
};

Cents operator-(const Cents& c1, const Cents& c2) {
  return Cents(c1.m_cents - c2.m_cents);
}

// =================================================================
// 3. Overloading operators using normal functions
// =================================================================
class Cents2 {
  public:
    Cents2(int cents): m_cents(cents) {}

    int getCents() const {
      return m_cents;
    }
  private:
    int m_cents;
};

// Overloading operator+ using a normal function, this is recommended way to overload operators,
// because it doesn't require the function to be a friend of the class to access the private members.
Cents2 operator+(const Cents2& c1, const Cents2& c2) {
  return Cents2(c1.getCents() + c2.getCents());
}

// Overloading operator<< using normal function
std::ostream& operator<<(std::ostream& out, const Cents2& cents) {
  out << cents.getCents() << " cents";
  return out;
}

// =================================================================
// 4. Overloading operators using member functions
// =================================================================
class Cents3 {
  public:
    Cents3(int cents): m_cents(cents) {}

    // Overloading operator+ using a member function
    // This class is the left operand, the right operand is passed as a parameter
    Cents3 operator+(const Cents3& c2) {
      return Cents3(m_cents + c2.m_cents);
    }
    // Overloading using a member function requires the left operand to be an object of the class,
    // which means that we can overload Cents3 + int using a member function,
    // but we can't overload int + Cents3 using a member function.

    int getCents() const {
      return m_cents;
    }
  private:
    int m_cents;
};

// =================================================================
// 5. Overloading using friend functions vs normal functions vs member functions
// =================================================================
// 1. Not all operators can be overloaded using friend functions, for example, the assignment operator '=', the scope resolution operator '::', the member selection operator '.', and the member selection operator '->', the call operator '()', the subscript operator '[]'
// 2. Not all operators can be overloaded using member functions, for example, we can't overload int + Cents3 using a member function, we can't overload operator<< using a member function,
//    (Because overloading using a member function requires the left operand to be an object of the class)
// 3. If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member function.
// 4. If you’re overloading a unary operator, do so as a member function.
// 5. If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function (preferred) or friend function.
// 6. If you’re overloading a binary operator that modifies its left operand, but you can’t add members to the class definition of the left operand (e.g. operator<<, which has a left operand of type ostream), do so as a normal function (preferred) or friend function.
// 7. If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), and you can modify the definition of the left operand, do so as a member function.

// =================================================================
// 6. Overloading typecast operators
// =================================================================
class Cents4 {
  public:
    Cents4(int cents): m_cents(cents) {}

    // Overloading typecast to int
    operator int() const {
      return m_cents;
    }

    int getCents() const {
      return m_cents;
    }
  private:
    int m_cents;
};

class Dollar {
  public:
    Dollar(int dollars): m_dollars(dollars) {}

    // Overloading typecast to Cents4, since it is marked as 'explicit', we can't use it for implicit type conversion,
    // we would have to use a static_cast to convert a Dollar object to a Cents4 object.
    explicit operator Cents4() const {
      return Cents4(m_dollars * 100);
    }

    int getDollars() const {
      return m_dollars;
    }
  private:
    int m_dollars;
};