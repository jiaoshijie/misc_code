/**
 * 1. 特殊乘法 2. 旋转矩阵(顺时针)
 * */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void specialMul();
void rotatingMatrix();

int main() {
  rotatingMatrix();
  return 0;
}

void specialMul() {
  int n1, n2, t1, t2, t, res = 0;
  while (true) {
    cin >> n1 >> n2;
    while (n1) {
      t1 = n1 % 10;
      n1 /= 10;
      t2 = n2;
      while (t2) {
        t = t2 % 10;
        t2 /= 10;
        res += t * t1;
      }
    }
    cout << res << endl;
    res = 0;
  }
}

void rotatingMatrix() {
  int n, flag = 0;
  cin >> n;
  int m1[9][9] = { 0 }, m2[9][9] = { 0 };
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> m1[i][j];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> m2[i][j];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (m1[i][j] != m2[i][j]) goto for_1;
      else if (i == n - 1 && j == n - 1) {
        flag = 0;
        goto result;
      }
    }
  }
for_1:
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (m1[i][j] != m2[j][n - 1 - i]) goto for_2;
      else if (i == n - 1 && j == n - 1) {
        flag = 1;
        goto result;
      }
    }
  }
for_2:
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (m1[i][j] != m2[n - 1 - i][n - 1 -j]) goto for_3;
      else if (i == n - 1 && j == n - 1) {
        flag = 2;
        goto result;
      }
    }
  }
for_3:
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (m1[i][j] != m2[n - 1 - j][i]) {
        cout << -1 << endl;
        return;
      } else if (i == n - 1 && j == n - 1) {
        flag = 3;
        goto result;
      }
    }
  }
result:
  cout << (int)(flag * 90) << endl;
}
