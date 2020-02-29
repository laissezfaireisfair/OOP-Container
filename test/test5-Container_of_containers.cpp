#include "Container.hpp"
#include <cstdint>
#include <iostream>
using namespace std;
using namespace Bicycle;

void print_int_container(Container<int> const & vec) {
  const uint64_t length = vec.get_length();
  for (uint64_t i = 0; i < length; ++i)
    cout << vec[i] << " ";
}

void print_matrix(Container<Container<int> > const & matrix) {
  const uint64_t sizeStr = matrix.get_length();
  for (uint64_t i = 0; i < sizeStr; ++i) {
    print_int_container(matrix[i]);
    cout << endl;
  }
}

int main() {
  cout << "Making vec of five int Containers..." << endl;
  Container<Container<int> > matrix(Container<int>(), 5);
  cout << "Setting values..." << endl;
  for (unsigned int i = 0; i < 5; ++i) {
    matrix[i] = Container<int>(0, 5);
    for (unsigned int j = 0; j < 5; ++j)
      matrix[i][j] = 10 * (i+1) + j + 1;
  }
  cout << "Printing matrix..." << endl;
  print_matrix(matrix);
  cout << "Matrix printed." << endl;
  return 0;
}
