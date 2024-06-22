#include <vector>

/**
 * https://en.cppreference.com/w/cpp/container/vector
 * 
 * std::vector is a sequence container that encapsulates dynamic size arrays.
 */

// Generate a set of examples for std::vector
void std_vector_examples() {
  // Create an empty vector
  std::vector<int> v1;

  // Create a vector with 5 elements, all initialized to 0
  std::vector<int> v2(5);

  // Create a vector with 5 elements, all initialized to 10
  std::vector<int> v3(5, 10);

  // Create a vector with elements from an array
  int arr[] = {1, 2, 3, 4, 5};
  std::vector<int> v4(arr, arr + 5);

  // Create a vector with elements from another vector
  std::vector<int> v5(v4.begin(), v4.end());

  // Access elements
  v5[0] = 10;
  v5.at(1) = 20;

  // Get the first element
  int first = v5.front();

  // Get the last element
  int last = v5.back();

  // Get the size of the vector
  int size = v5.size();

  // Check if the vector is empty
  bool empty = v5.empty();

  // Insert elements
  v5.push_back(30);
  v5.insert(v5.begin() + 1, 40);

  // Erase elements
  v5.pop_back();
  v5.erase(v5.begin() + 1);

  // Clear the vector
  v5.clear();

  // Iterate over the vector
  for (int i = 0; i < v4.size(); i++) {
    v4[i] *= 2;
  }

  for (std::vector<int>::iterator it = v4.begin(); it != v4.end(); it++) {
    *it *= 2;
  }

  for (int& x : v4) {
    x *= 2;
  }
}