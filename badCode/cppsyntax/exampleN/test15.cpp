/**
   中缀转后缀: 计算器
*/
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <vector>

using namespace std;

struct Hou {
  bool b; // false -> number, true -> char
  union {
    int num;
    char ch;
  };
  Hou(int i) : b(false), num(i) {}
  Hou(char ch) : b(true), ch(ch) {}
  void print() const {
    if (b) cout << ch;
    else cout << num;
  }
};

int priority(char ch) {
  if (ch == '+' || ch == '-')
    return 1;
  else if (ch == '*' || ch == '/')
    return 2;
  else if (ch == '^')
    return 3;
  return -1;
}

void create(const string& str, vector<Hou>& tar) {
  stack<char> s;
  for (auto it = str.begin(); it != str.end(); it++) {
    if (*it >= '0' && *it <= '9') {
      tar.push_back(Hou((int)(*it - '0')));
    } else {
      if (*it == ')') {
        while(s.top() != '(') {
          tar.push_back(Hou(s.top()));
          s.pop();
        }
        s.pop();
      } else if (*it == '(') {
        s.push(*it);
      } else if (!s.empty() && priority(s.top()) >= priority(*it)) {
        while(!s.empty() && priority(s.top()) >= priority(*it)) {
          tar.push_back(Hou(s.top()));
          s.pop();
        }
        s.push(*it);
      } else {
        s.push(*it);
      }
    }
  }
  while(!s.empty()) {
    tar.push_back(Hou(s.top()));
    s.pop();
  }
}

void Print(const vector<Hou>& h) {
  for (auto it = h.begin(); it != h.end(); it++) {
    it->print();
    if ((it + 1) == h.end()) {
      cout << endl;
    } else {
      cout << ' ';
    }
  }
}

int Pow(int i, int j) {
  int res = 1;
  while(j--) {
    res *= i;
  }
  return res;
}

void Count(vector<Hou>& s) {
  for (auto it = s.begin(); ; it++) {
    if (it->b) {
      if (it->ch == '+') {
        (it - 2)->num = (it - 2)->num + (it - 1)->num;
      } else if (it->ch == '-') {
        (it - 2)->num = (it - 2)->num - (it - 1)->num;
      } else if (it->ch == '*') {
        (it - 2)->num = (it - 2)->num * (it - 1)->num;
      } else if (it->ch == '/') {
        (it - 2)->num = (it - 2)->num / (it - 1)->num;
      } else if (it->ch == '^') {
        (it - 2)->num = Pow((it - 2)->num, (it - 1)->num);
      }
      s.erase(it - 1, it + 1);
      break;
    }
  }
}

int main() {
  string str;
  vector<Hou> tar;
  getline(cin, str);
  create(str, tar);
  Print(tar);
  while(tar.size() != 1) {
    Count(tar);
    Print(tar);
  }
  return 0;
}
