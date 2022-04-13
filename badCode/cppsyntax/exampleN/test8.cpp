/**
 * 1067 括号匹配
 * */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

stack<char> st;
string str;

int charpar(char c) {
  if (c == '}')
    return 5;
  else if (c == ']')
    return 6;
  else if (c == ')')
    return 7;
  else if (c == '>')
    return 8;
  else if (c == '<')
    return 1;
  else if (c == '(')
    return 2;
  else if (c == '[')
    return 3;
  else if (c == '{')
    return 4;
  else
    return 0;
}

int main() {
  int n;
  cin >> n;
  while(n--) {
    cin >> str;
    for (auto it = str.begin(); it != str.end(); it++) {
      if (!st.empty() && charpar(st.top()) < charpar(*it)) {
        if (charpar(st.top()) + charpar(*it) != 9) {
          break;
        } else {
          st.pop();
        }
      } else {
        st.push(*it);
      }
    }
    if (!st.empty()) {
      while(!st.empty()) st.pop();
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }
  return 0;
}
