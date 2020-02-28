#include "../include/Container.hpp"
#include <cstdint>
#include <iostream>
#include <string>
using namespace std;
using namespace Bicycle;

void print_string_container(Container<string> const & vec) {
  cout << "Printing vec..." << endl;
  const uint64_t length = vec.get_length();
  for (uint64_t i = 0; i < length; ++i)
    cout << vec[i] << " ";
  cout << endl << "Container printed." << endl << endl;
}

int main() {
  cout << "Making vec of five \"hello\"s..." << endl;
  Container<string> vec("hello", 5);
  print_string_container(vec);
  cout << "Setting first elem \"world\"..." << endl;
  vec[0] = "world";
  print_string_container(vec);
  return 0;
}
