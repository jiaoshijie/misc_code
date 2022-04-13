#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

int main() {
  int N;
  long long res = 1;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    res *= i;
    while(res % 10 == 0) res /= 10;
    // res %= 10; // TODO: 为什么对10取余不行
    res %= 1000000;
  }
  cout << res % 10 << endl;
  return 0;
}
