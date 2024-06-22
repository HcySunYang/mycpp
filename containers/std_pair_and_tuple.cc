#include <utility>
#include <tuple>
#include <string>

/**
 * https://en.cppreference.com/w/cpp/utility/pair
 * https://en.cppreference.com/w/cpp/utility/tuple
 */

// std::pair is a class template that provides a way to store two heterogeneous objects as a single unit.
void std_pair_examples() {
  // Create a pair of integers
  std::pair<int, int> p1 {1, 2};

  // Create a pair of a string and a double
  std::pair<std::string, double> p2 {"pi", 3.14};

  // Access the elements
  int first = p1.first;
  int second = p1.second;

  std::string str = p2.first;
  double d = p2.second;

  // Modify the elements
  p1.first = 10;
  p1.second = 20;

  p2.first = "e";
  p2.second = 2.718;

  // Create a pair of a pair and a tuple
  std::pair<int, std::tuple<int, int, int>> p3 {1, {2, 3, 4}};

  // Access the elements
  int outer = p3.first;
  int inner1 = std::get<0>(p3.second);
  int inner2 = std::get<1>(p3.second);
  int inner3 = std::get<2>(p3.second);

  // Modify the elements
  p3.first = 10;
  std::get<0>(p3.second) = 20;
  std::get<1>(p3.second) = 30;
  std::get<2>(p3.second) = 40;

  // Structured binding
  auto& [x, y] = p1;
  auto& [s, f] = p2;
  auto& [o, t] = p3;
}
// std::pair is standard-layout if both T1 and T2 are standard-layout types. For what is a standard-layout type, see:
// - https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
// - https://en.cppreference.com/w/cpp/language/data_members#Standard_layout
// - https://stackoverflow.com/questions/4178175/what-are-aggregates-and-trivial-types-pods-and-how-why-are-they-special/7189821#7189821