#include <iostream>
#include <string>
#include <vector>
#include <queue>

struct T1 {
  std::string str;
  int deletation;
  int index;
  T1(std::string str, int d, int i) : str(str), deletation(d), index(i) {}
};

int sum = 1;
std::string input;
std::queue<T1> q;

int main() {
  std::getline(std::cin, input);
  char lastch = '\0';
  for (int i = 0; i < input.size(); i++) {
    if (input[i] != lastch) {
      q.push(T1{input.substr(0, i) + input.substr(i + 1, input.size() - i - 1), 1, i});
      lastch = input[i];
      sum++;
    }
  }
  while(!q.empty() && q.front().deletation != 3) {
    std::string s = q.front().str;
    int index = q.front().index;
    char lastch = index ? s[index - 1] : '\0';
    for (; index < s.size(); index++) {
      if (s[index] != lastch) {
        q.push(T1{s.substr(0, index) + s.substr(index + 1, s.size() - index - 1), q.front().deletation + 1, index});
        lastch = s[index];
        sum++;
      }
    }
    q.pop();
  }
  std::cout << sum << std::endl;
  return 0;
}
