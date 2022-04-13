/**
 * 简单背包问题: 1035
 * */
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
#include <map>

using namespace std;

int Sum;
// std::vector<int> v;
int v[1024];

bool justice(int Count, const int index, const int len) {
  if (Count == Sum) {
    return true;
  }
  if (index == len || Count > Sum) {
    return false;
  }
  if (justice(Count, index + 1, len)) {
    return true;
  }
  return justice(Count + v[index], index + 1, len);
}

int main() {
  int Count, n;
  while(cin >> Sum >> n) {
    memset(v, 0, sizeof(int) * 1024);
    Count = 0;
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }
    if (justice(Count, 0, n)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}
