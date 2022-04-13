/**
* 如何优雅的使用常量
* 从#define, const 到constexpr
*/

#include <iostream>
#include <string>
#include <vector>
#include "const.hpp"

using std::cout;
using std::endl;
using std::string;

int numsquare(int num) {
  return num * num;
}

void touch_anyway_cpp() {  // cpp style
  const string name = "jiaoshijie";
  string& alias = const_cast<string&>(name);
  alias[0] = 'p';
  cout << name << endl;
}

void touch_anyway_c() {  // c style
  // from right to left
  const char *const name = "jiaoshijie";
  // name = nullptr;
  char *alias = (char*)name;
  alias[0] = 'p';
  printf("%s\n", name);
}

int main(int argc, char *argv[]) {
  // cout << numsquare(config::NUMS) << endl;
  touch_anyway_c();
  return 0;
}