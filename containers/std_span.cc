#include <span>
#include <array>
#include <vector>
#include <iostream>

/**
 * https://en.cppreference.com/w/cpp/container/span
 * 
 * std::span is a non-owning view over a contiguous sequence of objects.
 */

// A typical use case for std::span is to unify the interface of functions that operate on arrays and containers.

void print_container(std::span<int> s) {
  for (int i : s) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void std_span_examples() {
  // C-Style array
  int arr[] = {1, 2, 3, 4, 5};
  print_container(arr);

  // std::array
  std::array<int, 5> a {1, 2, 3, 4, 5};
  print_container(a);

  // std::vector
  std::vector<int> v {1, 2, 3, 4, 5};
  print_container(v);

  // std::span
  std::span<int> s {v};
  print_container(s);

  // std::span from a subsequence of a std::array
  std::span<int> s3 {a.data() + 1, 3};
  print_container(s3);

  // std::span from a subsequence of a C-Style array
  std::span<int> s4 {arr + 1, 3};
  print_container(s4);

  // std::span from a subsequence of a std::vector
  std::span<int> s5 {v.begin() + 1, 3};
  print_container(s5);
}