#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int N, M;
int *money;

bool *temp_m;

void print_m(int count) {
  int c = 0;
  for (int i = 0; i < N; i++) {
    if (temp_m[i]) {
      if (c != count - 1) {
        std::cout << money[i] << ' ';
        c++;
      }
      else {
        std::cout << money[i] << std::endl;
        return;
      }
    }
  }
}

bool cut(int cm, int index) {
  int res = cm;
  for (int i = index + 1; i < N; i++) {
    res += money[i];
    if (res > M) return true;
  }
  return res > M;
}

void dfs(int cm, int count, int index) {
  if (cm > M || index > N) return;
  if (cm == M) {
    print_m(count);
    exit(0);
  }
  temp_m[index] = true;
  dfs(cm + money[index], count + 1, index + 1);
  temp_m[index] = false;
  if (cut(cm, index))
    dfs(cm, count, index + 1);
}

int main() {
  std::cin >> N >> M;
  money = new int[N];
  temp_m = new bool[N];
  for (int i = 0; i < N; i++) {
    std::cin >> money[i];
  }
  std::sort(money, money + N);
  dfs(0, 0, 0);
  std::cout << "No Solution" << std::endl;
  return 0;
}
