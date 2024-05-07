
void autofn() {
  
  // Automatically deduce the type of a variable
  int a = 5;
  auto b = a; // b is an int
  auto& c = a; // c is an int&
  const auto d = a; // d is a const int, you can't modify it, otherwise you will get a compilation error
  auto* e = &a; // e is an int*
  const auto* f = &a; // f is a const int*, you can't modify the value of the object pointed by f, otherwise you will get a compilation error
  const auto* const g = &a; // g is a const pointer to const, so you can't modify the value the pointer points to, otherwise you will get a compilation error

  const int h = 10;
  // The constness of the variable is preserved if you deduce the type of a variable as a reference
  auto& i = h; // i is a const int&, you can't modify it, otherwise you will get a compilation error

}