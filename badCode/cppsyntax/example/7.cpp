#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 无重复二进制
void bincyc(int n);
bool justice_cyc(int *array, int len, int n);
int bin2dec(int *array, int s, int n, int len);
void printA(int *array, int len);

int main() {
  int n = 0;
  cout << "Enter a number: ";
  cin >> n;
  bincyc(n);
  return 0;
}

void printA(int *array, int len) {
  for (int i = 0; i < len; i++) {
    cout << array[i];
  }
  cout << endl;
}

// 无重复二进制
void bincyc(int n) {
  int len = (int)pow(2, n);
  int *arr_bin = new int[len];
  for (int i = 0; i < len / 2; i++) {
    arr_bin[i] = 1;
  }
  // printA(arr_bin, len);
  do {
    if (justice_cyc(arr_bin, len, n)) {
      printA(arr_bin, len);
      return;
    }
  }while(prev_permutation(arr_bin, arr_bin + len));
  cout << "无满足条件的情况\n";
}

bool justice_cyc(int *array, int len, int n) {
  int *arr_count = new int[len];
  int index = 0;
  for (int i = 0; i < len; i++) {
    index = bin2dec(array, i, n, len);
    if (arr_count[index] != 0) {
      return false;
    }
    arr_count[index] = 1;
  }
  return true;
}

int bin2dec(int *array, int s, int n, int len) {
  int res = 0;
  for (int i = 0; i < n; i++) {
    res += (int)pow(2, n - i - 1) * array[(s + i) % len];
  }
  return res;
}
