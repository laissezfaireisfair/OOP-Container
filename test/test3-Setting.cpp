#include "../include/Container.hpp"
#include "../src/Container.cpp"
#include <cstdint>
#include <iostream>
using namespace std;
using namespace Bicycle;

void print_int_container(Container<int> const & vec) {
  cout << "Printing vec..." << endl;
  const uint64_t length = vec.get_length();
  for (uint64_t i = 0; i < length; ++i)
    cout << vec[i] << " ";
  cout << endl << "Container printed." << endl << endl;
}

int main() {
  cout << "Making vec of five (111)s..." << endl;
  Container<int> vec(111, 5);
  print_int_container(vec);
  cout << "Setting first elem 54..." << endl << endl;
  vec[0] = 54;
  print_int_container(vec);
  cout << "Pop back elem..." << endl << endl;
  vec.pop_back();
  print_int_container(vec);
  cout << "Cleaning..." << endl << endl;
  vec.clean();
  print_int_container(vec);
  cout << "Push back 14..." << endl << endl;
  vec.push_back(14);
  print_int_container(vec);
  cout << "vec[0] *= 2..." << endl << endl;
  vec[0] *= 2;
  print_int_container(vec);
  return 0;
}
