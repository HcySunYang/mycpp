#include <cstdint>
/*
* 1. Enum class (scoped enumeration)
*/


// =================================================================
// 1. Enum class (scoped enumeration)
// =================================================================
// Basic enum class
// Enum class don't implicitly convert to integer, but we can do it explicitly by using static_cast, for example,
// static_cast<int>(Color::RED)
enum class Color {
  RED,
  GREEN,
  BLUE
};
// The default type of the enum class is int, so its size is the same as int
Color clr {Color::RED};

// Enum class with 8 bits of unsigned integer of underlying type
enum class Color8 : uint8_t {
  RED = 0,
  GREEN,
  BLUE
};

// Enum class can have different enumerators with the same value
enum class Month: uint8_t {
  JAN = 1,
  JANUARY = JAN,
  FEB = 2,
  FEBRUARY = FEB,
  MAR = 3,
  MARCH = MAR,
  APR = 4,
  APRIL = APR,
  MAY = 5,
  JUN = 6,
  JUNE = JUN,
  JUL = 7,
  JULY = JUL,
  AUG = 8,
  AUGUST = AUG,
  SEP = 9,
  SEPTEMBER = SEP,
  OCT = 10,
  OCTOBER = OCT,
  NOV = 11,
  NOVEMBER = NOV,
  DEC = 12,
  DECEMBER = DEC,
};

// using enum
void fn1() {
  using enum Month;
  // We can then use the enumerators without the enum class name
  Month m = JAN;
}