#include "Container.hpp"
#include <cstdint>
#include <iostream>
#include <string>
using namespace std;
using namespace Bicycle;

class UI {
public:
  static void ok() {
    cout << "- OK" << endl;
  }
  static void wrong () {
    cout << "- WRONG" << endl;
  }
  static void emptyTesting() {
    cout << "Testing empty vec ...                       ";
  }
  static void certainCapacityTesting() {
    cout << "Testing empty vec with certain capacity ... ";
  }
  static void resizeTesting() {
    cout << "Testing resize ...                          ";
  }
  static void reserveTesting() {
    cout << "Testing reserve ...                         ";
  }
  static void shrinkToFitTesting() {
    cout << "Testing shrink to fit ...                   ";
  }
  static void print_int_vec(Container<int> const & vec) {
    cout << "Printing vec..." << endl;
    const uint64_t length = vec.get_length();
    cout << "Length: " << length << endl;
    cout << "Capacity: " << vec.get_capacity() << endl;
    for (uint64_t i = 0; i < length; ++i)
      cout << vec[i] << " ";
    cout << endl << "Vector printed." << endl << endl;
  }
};

int main() {
  UI::emptyTesting();
  Container<int> vec = Container<int>();
  if (vec.get_length() == 0 && vec.get_capacity() == 1)
    UI::ok();
  else {
    UI::wrong();
    UI::print_int_vec(vec);
    return 1;
  }

  UI::certainCapacityTesting();
  Container<int> vec2 = Container<int>(13);
  if (vec2.get_length() == 0 && vec2.get_capacity() == 13)
    UI::ok();
  else {
    UI::wrong();
    UI::print_int_vec(vec2);
    return 2;
  }


  UI::resizeTesting();
  vec2.resize(1);
  if (vec2.get_length() == 1 && vec2.get_capacity() == 13)
    UI::ok();
  else {
    UI::wrong();
    UI::print_int_vec(vec2);
    return 3;
  }

  UI::reserveTesting();
  vec.reserve(5);
  if (vec.get_length() == 0 && vec.get_capacity() == 5)
    UI::ok();
  else {
    UI::wrong();
    UI::print_int_vec(vec);
    return 4;
  }

  UI::shrinkToFitTesting();
  vec2.shrink_to_fit();
  if (vec.get_length() == 1 && vec.get_capacity() == 1)
    UI::ok();
  else {
    UI::wrong();
    UI::print_int_vec(vec2);
    return 5;
  }

  return 0;
}
