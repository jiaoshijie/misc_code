#include <iostream>
#include <string>
#include <vector>
#include <queue>

int sum = 1;
std::string input;

void dfs(std::string str, int i, int d) {
  if (d > 2) return;
  char lastch = i ? str[i - 1] : '\0';
  for (; i < str.size(); i++) {
    if (str[i] != lastch) {
      sum++;
      lastch = str[i];
      dfs(str.substr(0, i) + str.substr(i + 1, str.size() - i - 1), i, d + 1);
    }
  }
}

int main() {
  std::getline(std::cin, input);
  dfs(input, 0, 0);
  std::cout << sum << std::endl;
  return 0;
}
