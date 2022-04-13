/**
 * Stack and Quene
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

void stacktest();
void queuetest();

int main() {
  queuetest();
  return 0;
}

void stacktest() {
  int c = 0;
  string input;
  stack<char> st;
  cin >> c;
  getchar();
  while(c--) {
    getline(cin, input);
    for (auto it = input.begin(); it != input.end(); it++) {
      if (*it != ' ') {
        st.push(*it);
      } else {
        while(!st.empty()) {
          cout << st.top();
          st.pop();
        }
        cout << ' ';
      }
    }
    while(!st.empty()) {
      cout << st.top();
      st.pop();
    }
    cout << endl;
  }
}

void queuetest() {
  int c = 0, oc = 0, temp;
  string method, operation;
  queue<int> qu;
  stack<int> st;
  cin >> c;
  while(c--) {
    cin >> oc >> method;
    while (oc--) {
      cin >> operation;
      if (method == "FIFO") {
        if (operation == "IN") {
          cin >> temp;
          qu.push(temp);
        } else if (operation == "OUT") {
          if (qu.empty()) cout << "None" << endl;
          else {
            cout << qu.front() << endl;
            qu.pop();
          }
        }
      } else if (method == "FILO") {
        if (operation == "IN") {
          cin >> temp;
          st.push(temp);
        } else if (operation == "OUT") {
          if (st.empty()) cout << "None" << endl;
          else {
            cout << st.top() << endl;
            st.pop();
          }
        }
      }
    }
    while(!qu.empty()) qu.pop();
    while(!st.empty()) st.pop();
  }
}
