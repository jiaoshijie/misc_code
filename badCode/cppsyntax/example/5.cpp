#include <iostream>
#include <string>
#include <vector>

using namespace std;

int thirdPower(int n) {
  return n * n * n;
}

// 水仙花数
void flowerNumber() {
  for (int i = 100; i < 1000; i++) {
    if (i == thirdPower(i / 100) + thirdPower((i % 100) / 10) + thirdPower(i % 10))
      cout << i << endl;
  }
}

// 螺旋矩阵 递归
void matrixD(const int n, int **array, const int s) {
  static int num = 1;
  if (n == 0) {
    return;
  }
  if (n == 1) {
    array[s][s] = num++;
    return;
  }
  for (int i = s; i < n + s - 1; i++) {
    array[s][i] = num++;
  }
  for (int i = s; i < n + s - 1; i++) {
    array[i][n + s - 1] = num++;
  }
  for (int i = n + s - 1; i > s; i--) {
    array[n + s - 1][i] = num++;
  }
  for (int i = n + s - 1; i > s; i--) {
    array[i][s] = num++;
  }
  matrixD(n - 2, array, s + 1);
}

void printA(int **array, const int len) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      cout << array[i][j] << "\t";
    }
    cout << endl;
  }
}

// 迭代
void matrix(int n, int **array, int s) {
  int num = 1;
  while (true) {
    if (n == 0) {
      break;
    }
    if (n == 1) {
      array[s][s] = num++;
      break;
    }
    for (int i = s; i < n + s - 1; i++) {
      array[s][i] = num++;
    }
    for (int i = s; i < n + s - 1; i++) {
      array[i][n + s - 1] = num++;
    }
    for (int i = n + s - 1; i > s; i--) {
      array[n + s - 1][i] = num++;
    }
    for (int i = n + s - 1; i > s; i--) {
      array[i][s] = num++;
    }
    n = n - 2;
    s = s + 1;
  }
}

// 求[a, b] 0~9出现的次数
int *countNum(int a, int b) {
  int *array = new int[10]{ 0 };
  int temp = 0;
  for (int i = a; i <= b; i++) {
    temp = i;
    while (temp) {
      array[temp % 10]++;
      temp = temp / 10;
    }
  }
  return array;
}

int main() {
  // int n = 0;
  // cin >> n;
  // int **array = new int*[n];
  // for (int i = 0; i < n; i++) {
  //   array[i] = new int[n]{ 0 };
  // }
  // matrix(n, array, 0);
  // printA(array, n);
  int a, b;
  cin >> a >> b;
  int *array = countNum(a, b);
  for (int i = 0; i < 10; i++) {
    cout << i << "->" << array[i] << endl;
  }
  return 0;
}
