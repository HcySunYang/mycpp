#include <iterator>
#include <vector>

/**
 * https://en.cppreference.com/w/cpp/iterator
 * 
 * The C++ Standard Library provides a set of iterator types that can be used to traverse sequences of elements.
 */

void test_iterator() {
  std::vector<int> v1 {1, 2, 3, 4, 5};
  std::vector<int>::iterator it { v1.begin() };
  std::vector<int>::iterator end { v1.end() };
  *(it++) = 10;

  // const iterator
  std::vector<int>::const_iterator cit { v1.cbegin() };
  std::vector<int>::const_iterator cend { v1.cend() };

  // reverse iterator
  std::vector<int>::reverse_iterator rit { v1.rbegin() };
  std::vector<int>::reverse_iterator rend { v1.rend() };

  // const reverse iterator
  std::vector<int>::const_reverse_iterator crit { v1.crbegin() };
  std::vector<int>::const_reverse_iterator crend { v1.crend() };

  // Calculate the distance between two iterators
  std::vector<int>::iterator it1 { v1.begin() };
  std::vector<int>::iterator it2 { v1.begin() + 3 };
  std::ptrdiff_t distance = std::distance(it1, it2);

  // Advance an iterator
  std::vector<int>::iterator it3 { v1.begin() };
  std::advance(it3, 3);

  // Next and prev
  // Not all containers support the it + n and it - n operations. Use std::next and std::prev instead.
  std::vector<int>::iterator it4 { v1.begin() };
  std::vector<int>::iterator next = std::next(it4, 3);
  std::vector<int>::iterator prev = std::prev(it4, 3);

  // range-based for loop
  for (int i : v1) {
    // Do something with i
  }

  // Iterator traits. TODO: What is this?
  // std::iterator_traits<std::vector<int>::iterator>::value_type value_type;
  // std::iterator_traits<std::vector<int>::iterator>::difference_type difference_type;
  // std::iterator_traits<std::vector<int>::iterator>::pointer pointer;
  // std::iterator_traits<std::vector<int>::iterator>::reference reference;
  // std::iterator_traits<std::vector<int>::iterator>::iterator_category iterator_category;

}