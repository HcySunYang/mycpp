/**
 * 1. Class template in basic
 * 2. Non-type template parameters
 * 3. Class template specialization (and partial specialization)
 * 4. Member function specialization (and partial specialization)
 */

// =================================================================
// 1. Class template in basic
// =================================================================
template <typename T>
class Array {
  public:
    Array(size_t length) : length(length) {
      ptr = new T[length];
    }

    // It is worth noting that inside the class we can use non-templated type name directly, the Array in this case,
    // but outside the class we must use the templated type name, Array<T>, because the Array outside of the class
    // refers to the non-templated version of a class named Array.
    Array(const Array& arr) = delete;
    Array& operator=(const Array& arr) = delete;

    ~Array() {
      delete[] ptr;
    }

    void erase() {
      delete[] ptr;
      ptr = nullptr;
      length = 0;
    }

    // This will be defined outside the class
    T& operator[](size_t index);

  private:
    T* ptr;
    size_t length;
};


// If we define the member function outside the class definition, we need to specify the template parameter again,
// we also need to qualify the member function name with the fully templated name, i.e. Array<T>::operator[].
// We must use Array<T> here, not Array, Array refers to a non-templated of a class named Array.
template <typename T>
T& Array<T>::operator[](size_t index) {
  assert(index >= 0 && index < length);
  return ptr[index];
}

// =================================================================
// 2. Non-type template parameters
// =================================================================
// Non-type template parameters are template parameters that are not types. They can be:
// - An integral type
// - An enumeration type
// - A pointer or reference to a class object
// - A pointer or reference to a function
// - A pointer or reference to a class member function
// - std::nullptr_t
// - A floating point type (since C++20)
template <typename T, size_t size>
class StaticArray {
  public:
    T& operator[](size_t index) {
      assert(index >= 0 && index < size);
      return m_array[index];
    }
  private:
    T m_array[size] {};
};

// Example of using non-type template parameters
void test_static_array() {
  // The non-type template parameter must be a constant expression
  StaticArray<int, 12> intArray;
  StaticArray<double, 4> doubleArray;
}

// =================================================================
// 3. Class template specialization (and partial specialization)
// =================================================================
// Class template specialization is a way to provide a different implementation for a specific type.
template <>
class StaticArray<bool, 10> {
  // Specialized class template doesn't need to have the same member functions as the primary template,
  // it is completely independent.
  public:
    void set(size_t index) {
      assert(index >= 0 && index < 10);
      m_array[index] = true;
    }

    void reset(size_t index) {
      assert(index >= 0 && index < 10);
      m_array[index] = false;
    }

    bool get(size_t index) {
      assert(index >= 0 && index < 10);
      return m_array[index];
    }

  private:
    bool m_array[10] {};
};
// Partial specialization of a class
template <size_t length>
class StaticArray<double, length> {
  public:
    double& operator[](size_t index) {
      assert(index >= 0 && index < length);
      return m_array[index];
    }
  private:
    double m_array[length] {};
};

// =================================================================
// 4. Member function specialization (and partial specialization)
// =================================================================
template <>
int& StaticArray<int, 100>::operator[](size_t index) {
  assert(index >= 0 && index < 100);
  return m_array[index];
}

// Partial specialization of a function is not allowed, the same happens to a member function of a class template as well.
// In C++, we use base template class and inheritance to achieve the specialization of a member function.
template <typename T, size_t size>
class BaseStaticArray {
  public:
    T& operator[](size_t index) {
      assert(index >= 0 && index < size);
      return m_array[index];
    }
  protected:
    T m_array[size] {};
};

template <size_t length>
class DerivedStaticArray : public BaseStaticArray<double, length> {
  public:
    double& operator[](size_t index) {
      return BaseStaticArray<double, length>::m_array[index];
    }
};