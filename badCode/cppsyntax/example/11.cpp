/**
* 并查集
* https://zh.wikipedia.org/zh-cn/%E5%B9%B6%E6%9F%A5%E9%9B%86
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int findP(int *Set, int c);
void merge(int *Set, int x, int y);
void city();
int justiceSetNum(int *Set, int len);

int main() {
  city();
  return 0;
}

int findP(int *Set, int c) {
  if (Set[c] == c) return c;
  return findP(Set, Set[c]);
}

void merge(int *Set, int x, int y) {
  int i = findP(Set, x);
  int j = findP(Set, y);
  if (i != j) Set[i] = j;
}

void city() {  // TODO 使用dfs() 实现判断
  int cityNum, roadNum;
  int t1, t2;
  cin >> cityNum >> roadNum;
  int *Set = new int[cityNum + 1];
  for (int i = 0; i <= cityNum; i++) {
    Set[i] = i;  // 每一个点为一个集合
  }
  while (roadNum--) {
    cin >> t1 >> t2;
    merge(Set, t1, t2);
  }
  cout << justiceSetNum(Set, cityNum + 1) - 1<< endl;
}

int justiceSetNum(int *Set, int len) {
  int sum = 0;
  for (int i = 1; i < len; i++) {
    if (Set[i] == i) sum++;
  }
  return sum;
}
