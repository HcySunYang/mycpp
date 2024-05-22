template<typename T>
class Pair {
  public:
    // we can use the type template parameter directly for member functions
    Pair(const T& first, const T& second) : first(first), second(second) {}

    T GetFirst() const;
  private:
    T first;
    T second;
};

// If we define the member function outside the class definition, we need to specify the template parameter again,
// we also need to qualify the member function name with the fully templated name, i.e. Pair<T>::GetFirst
template<typename T>
T Pair<T>::GetFirst() const {
  return first;
}