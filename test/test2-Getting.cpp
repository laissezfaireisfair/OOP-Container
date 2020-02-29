#include "../include/Container.hpp"
#include <cstdint>
#include <iostream>
using namespace std;
using namespace Bicycle;

void print_int_container(Container<int> const & vec) {
  const uint64_t length = vec.get_length();
  for (uint64_t i = 0; i < length; ++i)
    cout << vec[i] << " ";
}

int main() {
  cout << "Making vec of five (666)s..." << endl;
  Container<int> vec(666, 5);
  cout << "Length: " << vec.get_length() << endl;
  cout << "Capacity: " << vec.get_capacity() << endl;
  cout << "Is empty: " << (vec.is_empty() ? "True" : "False") << endl;
  cout << "Front value: " << vec.get_front() << endl;
  cout << "Back value: " << vec.get_back() << endl;
  cout << "Printing vec..." << endl;
  print_int_container(vec);
  cout << endl << "Container printed." << endl;
  return 0;
}
