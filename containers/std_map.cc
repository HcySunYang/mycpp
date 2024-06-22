#include <map>
#include <string>

/**
 * https://en.cppreference.com/w/cpp/container/map
 * 
 * std::map is a sorted associative container that contains key-value pairs with unique keys.
 */

// Generate a set of examples for std::map
void std_map_examples() {
  // Create an empty map
  std::map<int, std::string> m1;

  // Create a map with elements
  std::map<int, std::string> m2 {
    {1, "one"},
    {2, "two"},
    {3, "three"}
  };

  // Access elements
  std::string value = m2[1];
  std::string value2 = m2.at(2);

  // Modify elements
  m2[1] = "uno";
  m2.at(2) = "dos";

  // Insert elements
  m2.insert({4, "four"});

  // Erase elements
  m2.erase(1);

  // Clear the map
  m2.clear();

  // Check if the map is empty
  bool empty = m2.empty();

  // Get the size of the map
  int size = m2.size();

  // Iterate over the map
  for (const auto& [key, value] : m1) {
    // Do something with key and value
  }

  for (std::map<int, std::string>::iterator it = m2.begin(); it != m2.end(); it++) {
    // Do something with it->first and it->second
  }
}