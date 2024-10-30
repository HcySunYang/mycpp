#include <mutex>

/**
 * 1. constexpr and constinit
 * 2. thread_local
 * 3. mutable specifier
 */

// =================================================================
// 1. constexpr and constinit
// =================================================================
// constexpr is a keyword that tells the compiler that a function or object can be evaluated at compile time.
// constinit is a keyword that tells the compiler that an object must be initialized at compile time. It is
// used to solve the static initialization order fiasco problem: https://isocpp.org/wiki/faq/ctors#static-init-order,
// we usually fix this issue using so-called "magic statics" or "construct on first use" idiom.
// In C++20, constinit is introduced to solve this problem in a more elegant way.
// Chromium uses the ABSL_CONST_INIT macro to ensure that an object is initialized at compile time, which comes from the
// open-source library Abseil: https://github.com/abseil/abseil-cpp
constexpr int len {10}; // constexpr variable, it can be used as the length of an array
constinit int x = 10; // constexpr implies constinit, but constinit implies the object must be initialized at compile time
// Search for constexpr in this repo to see the information about constexpr function

// constexpr constructor.
// By default, only built-in types could be valid constant expressions, with constexpr constructor, we can create
// a user-defined type that can be used as a constant expression. There are lots of rules to follow to make a constructor
// constexpr: https://www.ibm.com/docs/en/xl-c-and-cpp-aix/13.1.0?topic=constructors-constexpr-c11
class Point {
  public:
    constexpr Point(int x, int y) : x_(x), y_(y) {}
    constexpr int x() const { return x_; }
    constexpr int y() const { return y_; }
  private:
    int x_;
    int y_;
};
constexpr Point p {1, 2};

// =================================================================
// 2. thread_local
// =================================================================
// thread_local is a keyword that tells the compiler that a variable has thread storage duration,
// and each thread has its own instance of the variable.
constinit thread_local int thread_local_var = 10;

// =================================================================
// 3. mutable specifier
// =================================================================
// mutable is a keyword that tells the compiler that a member variable of a class can be modified even if the
// member function is a const member function. This is useful when you want to cache the result of a computation
// in a member variable, one common use case is the thread safe counter:
class Counter {
  public:
    int get() const {
      std::lock_guard<std::mutex> lock(mutex_);
      return count_;
    }
    void increment() const {
      std::lock_guard<std::mutex> lock(mutex_);
      ++count_;
    }
  private:
    mutable int count_ {0};
    mutable std::mutex mutex_;
};