/**
   拱猪游戏 - 1065
   */
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

struct Player {
  const int H_table[13] = {-50, -2, -3, -4, -5, -6, -7, -8, -9, -10, -20, -30, -40};
  bool H[13];
  bool S12, D11, C10;
  int count;
  Player() : S12(false), D11(false), C10(false), count(0){
    memset(H, 0, sizeof(bool) * 13);
  }
  void insert(const string& str) {  // 插入数据
    if (str == "S12") S12 = true;
    else if (str == "D11") D11 = true;
    else if (str == "C10") C10 = true;
    else if (str[0] == 'H'){
      H[stoi(str.substr(1, 2)) - 1] = true;  // 1-13 -> 0-12
    }
  }

  bool is_HaveAllH() const {  // 是否拥有全部的红心牌
    for (int i = 0; i < 13; i++) {
      if (!H[i]) return false;
    }
    return true;
  }

  int is_Double(int scores) {  // 是否加倍
    if (C10) return scores * 2;
    return scores;
  }

  int getHscores() {
    int res = 0;
    if (is_HaveAllH()) {
      res += is_Double(200);
    } else {
      for (int i = 0; i < 13; i++) {
        if (H[i]) {
          res += is_Double(H_table[i]);
        }
      }
    }
    return res;
  }
  int getS12andD11scores() {
    int res = 0;
    if (is_HaveAllH() && S12 && D11) {
      res += is_Double(500);
      res -= is_Double(200);
    } else {
      res += S12 ? is_Double(-100) : 0;
      res += D11 ? is_Double(100) : 0;
    }
    return res;
  }
  void Count() {
    count += getS12andD11scores();
    count += getHscores();
    count += !count && !S12 && !D11 && C10 ? 50 : 0;
  }
  void print() {
    // if (count == 0) cout << 0;
    // else cout << std::showpos << count;
    if (count > 0) cout << '+' << count;
    else cout << count;
  }
};

bool check(int *N) {
  for (int i = 0; i < 4; i++) {
    if (N[i]) return false;
  }
  return true;
}

int main() {
  while(true) {
    int N[4];
    string temp;
    Player player[4];
    for (int i = 0; i < 4; i++) {
      cin >> N[i];
      for (int j = 0; j < N[i]; j++) {
        cin >> temp;
        player[i].insert(temp);
      }
      player[i].Count();
    }
    if (check(N)) break;
    for (int i = 0; i < 4; i++) {
      player[i].print();
      if (i == 3) cout << endl;
      else cout << ' ';
    }
  }
  // cout << std::showpos << p.count << endl;
  return 0;
}
