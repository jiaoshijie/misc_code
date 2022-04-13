#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int N;
std::vector<std::string> info;
std::vector<int> res;
bool *flag;

void print_res() {
  int count = 0;
  for (int i = 0; i < N; i++) {
    count++;
    std::cout << res[i] + 1;
    if (count == N) std::cout << std::endl;
    else std::cout << ' ';
  }
}

bool done() {
  if (res.size() == N) {
    return (info[res.back()][res.front()] == 'W' || info[res.front()][res.back()] == 'L');
  }
  return false;
}
bool cut() {
  for (int i = 0; i < N; i++) {
    if (!flag[i] && (info[i][res.front()] == 'W' || info[res.front()][i] == 'L'))
      return true;
  }
  return false;
}

void dfs(int prev) {
  for (int i = 0; i < N; i++) {
    if (!flag[i] && (info[prev][i] == 'W' || info[i][prev] == 'L')) {
      res.push_back(i);
      flag[i] = true;
      dfs(i);
      res.pop_back();
      flag[i] = false;
    }
    if (done()) {
      print_res();
      exit(0);
    }
    if (!cut()) return;
  }
}

void run() {
  for (int i = 0; i < N; i++) {
    res.push_back(i);
    flag[i] = true;
    dfs(i);
    res.pop_back();
    flag[i] = false;
  }
}

int main() {
  std::cin >> N;
  getchar();  // clear '\n'
  for (int i = 0; i < N; i++) {
    std::string t;
    std::getline(std::cin, t);
    info.push_back(t);
  }
  flag = new bool{ false };
  run();
  std::cout << "No Solution" << std::endl;
  return 0;
}
