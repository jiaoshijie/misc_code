/**
 * 素数: 只能被1和本身整除
 * 合数
 * 1 既不是素数也不是合数
 * */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool prime_number(int n) {
  if (n <= 1) return false;
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) return false;
  }
  return true;
}

int* prime_number01(int n) {
  int *Array = new int[n + 1]{ 0 };
  Array[1] = -1;
  int num = 0;
  for (int i = 2; i <= sqrt(n); i++) {
    if (Array[i] == 0) {
      num = 2;
      while (i * num <= n) {
        Array[i * num++] = 1;
      }
    }
  }
  return Array;
}

// 欧拉筛 1-n
// 1. 删除特殊的1
// 2. 从2开始枚举数i, 若没有被删掉, 则加入素数表
// 3. 枚举素数表中的每一个素数j, 并将i*j的结果从表中删除
vector<int> prime_number02(int n) {
  int *array = new int[n + 1]{ 0 };
  vector<int> primeA;
  array[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (array[i] == 0) primeA.push_back(i);
    for (int j = 0; j < (int)primeA.size() && i * primeA[j] <= n; j++) {
      array[i * primeA[j]] = 1;
    }
  }
  delete array;
  return primeA;
}

int main() {
  // if (prime_number(4)) cout << "It's a prime number." << endl;

  int *Array = prime_number01(100);
  int count = 0;
  for (int i = 1; i <= 100; i++) {
    if (Array[i] == 0) {
      cout << i << "\t";
      count++;
    }
    else
      cout << "-\t";
    if (i % 10 == 0) cout << endl;
  }
  cout << count << endl;

  // vector<int> array = prime_number02(100);
  // for (auto it = array.begin(); it != array.end(); it++) {
  //   cout << *it << endl;
  // }
  // cout << array.size() << endl;
  return 0;
}
