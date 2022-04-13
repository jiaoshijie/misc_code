#include <iostream>

const int v = 6;  // 顶点数

int edge[v][v] = {  // 边集
  {0, 1, 0, 1, 1, 0},
  {1, 0, 1, 0, 1, 1},
  {0, 1, 0, 0, 1, 1},
  {1, 0, 0, 0, 1, 0},
  {1, 1, 1, 1, 0, 1},
  {0, 1, 1, 0, 1, 0}
};

// int edge[v][v];
int bestn;  // 最大团顶点个数
int cn;
int besta[v];  // 最大团顶点
int a[v];

void backtrack(int i) {
  if (i >= v) {
    if (cn > bestn) {
      bestn = cn;
      for (int j = 0; j < v; j++) {
        besta[j] = a[j];
      }
    }
    return;
  }
  bool ok = true;
  for (int j = 0; j < i; j++) {
    // 判断当前顶点和已经入选的顶点是否有边相连
    if (a[j] && !edge[j][i]) {
      ok = false;
      break;
    }
  }
  if (ok) {
    a[i] = 1;
    cn++;
    backtrack(i + 1);
    a[i] = 0;
    cn--;
  }
  if (cn + v - i > bestn) {
    a[i] = 0;
    backtrack(i + 1);
  }
}

int main() {
  backtrack(0);
  for (int i = 0; i < v; i++) {
    if (besta[i]) {
      std::cout << i + 1 << ' ';
    }
  }
  std::cout << std::endl;
  return 0;
}
