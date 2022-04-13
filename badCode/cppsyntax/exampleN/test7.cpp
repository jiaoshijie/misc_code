#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool justice(int num) {
  int m = sqrt(num) + 1;
  for (int i = 2; i < m; i++) {
    if (num % i == 0) return false;
  }
  return true;
}

int main() {
  int num;
  cin >> num;
  if (num < 2) num = 2;  // NOTE 1既不是素数(质数), 也不是合数
  while(true) {
    if (justice(num)) {
      cout << num << endl;
      break;
    }
    num++;
  }
  return 0;
}
