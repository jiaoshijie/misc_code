/**
* BFS
* */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

using std::cout;
using std::endl;
using std::string;

// 1. 二叉树的最小高度
int mixTreeD(int *Tree, int len);
// 2. 最小密码锁
int mixSuo(const string *deadends, int dlen, const string target);
string plusStr(string str, int i);
string minusStr(string str, int i);

int main() {
  // cout << mixTreeD(new int[7]{3, 9, 20, 1, 1, 15, 7}, 7) << endl;
  // string deadends[] = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
  string deadends[] = {"0201", "0101", "0102", "1212", "2002"};
  cout << mixSuo(deadends, sizeof(deadends) / sizeof(string), "0202") << endl;
  return 0;
}

int mixTreeD(int *Tree, int len) {
  int depth = 1, index = 0;
  std::queue<int> qu;
  // std::set<int> s;
  qu.push(0);
  while(!qu.empty()) {
    int qulen = qu.size();
    for (int i = 0; i < qulen; i++) {
      index = qu.front();
      qu.pop();
      if ((index * 2 + 1 >= len || index * 2 + 2 >= len) || (Tree[index * 2 + 1] == 0 && Tree[index * 2 + 2] == 0)) {
        return depth;
      }
      if (Tree[index * 2 + 1] != 0) {
        qu.push(index * 2 + 1);
      }
      if (Tree[index * 2 + 2] != 0) {
        qu.push(index * 2 + 2);
      }
    }
    depth++;
  }
  return depth;
}

string plusStr(string str, int i) {
  string s = str;
  if (s[i] == '9') s[i] = '0';
  else s[i]++;
  return s;
}

string minusStr(string str, int i) {
  string s = str;
  if (s[i] == '0') s[i] = '9';
  else s[i]--;
  return s;
}

int mixSuo(const string *deadends, int dlen, const string target) {
  int depth = 1;
  string attempt = "0000", temp;
  std::unordered_set<string> deadendl;
  for (int i = 0; i < dlen; i++) {
    deadendl.insert(deadends[i]);
  }
  std::unordered_set<string> visited;
  std::queue<string> qu;
  qu.push(attempt);
  while(!qu.empty()) {
    int len = qu.size();
    for (int j = 0; j < len; j++) {
      attempt = qu.front();
      qu.pop();
      for (int i = 0; i < 4; i++) {
        temp = plusStr(attempt, i);
        if (temp == target) return depth;
        if (deadendl.find(temp) == deadendl.end() && visited.find(temp) == visited.end()) {
          deadendl.insert(temp);
          visited.insert(temp);
          qu.push(temp);
        }
        temp = minusStr(attempt, i);
        if (temp == target) return depth;
        if (deadendl.find(temp) == deadendl.end() && visited.find(temp) == visited.end()) {
          deadendl.insert(temp);
          visited.insert(temp);
          qu.push(temp);
        }
      }
    }
    depth++;
  }
  return -1;
}
