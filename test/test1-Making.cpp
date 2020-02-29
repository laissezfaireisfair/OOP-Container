#include "Container.hpp"
#include <iostream>
using namespace std;
using namespace Bicycle;

int main() {
  cout << "Making vec with default constructor..." << endl;
  Container<int> vecDefault;
  cout << "Making vec with copy constructor..." << endl;
  Container<int> vecCopy = vecDefault;
  cout << "Making vec with value constructor..." << endl;
  Container<int> vecValues(666, 5);
  cout << "All vectors was made." << endl;
  return 0;
}
