/**
* 两个数的最大公因数(gcd): 1. 辗转相除法 2. 更相减损法
* 最小公倍数: = (a * b)/gcd(a,b)
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 1. 辗转相除法
void func01(long num1, long num2) {
  while (num1 && num2) {
    if (num1 > num2) {
      num1 %= num2;
    } else if (num1 < num2) {
      num2 %= num1;
    }
  }
  cout <<  (num1 > num2 ? num1 : num2) << endl;
}

// 2. 更相减损法
void func02(long num1, long num2) {
  while (num1 != num2) {
    if (num1 > num2) {
      num1 -= num2;
    } else if (num1 < num2) {
      num2 -= num1;
    }
  }
  cout << num1 << endl;
}

/** 最小公倍数 **/
void lcm(long num1, long num2) {
  cout << num1 / __gcd(num1, num2) * num2 << endl;  // 防止溢出
}

int main() {
  lcm(18, 12);
  return 0;
}
