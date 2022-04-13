#include <iostream>
#include "CPPTimer.hpp"

const int len = 10000000;

int arr[len];

int main() {
  // do something
  {
    // testing running time
    CPPTimer t;
    for (int i = 0; i < len; i++) {
      arr[i] = i;
    }
  }
  // do other thing
  return 0;
}