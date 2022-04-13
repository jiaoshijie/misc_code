/**
 * 划动窗口算法
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;

bool justice(std::unordered_map<char, int>& needs, std::unordered_map<char, int>& window);
void updatelr(int left, int right, int& resl, int& resr);
string minWindow(string& s, string& t);

/**
 * Main function(method)
*/
int main() {
  string s = "ADOBECODEBANC";
  string t = "ABC";
  cout << minWindow(s, t) << endl;
  return 0;
}

bool justice(std::unordered_map<char, int>& needs, std::unordered_map<char, int>& window) {
  for (std::unordered_map<char, int>::iterator it = needs.begin(); it != needs.end(); it++) {
    if (window[it->first] < 1) return false;
  }
  return true;
}

void updatelr(int left, int right, int& resl, int& resr) {
  if (right - left > 0 && right - left < resr - resl) {
    resr = right;
    resl = left;
  }
}

// 最小字串
string minWindow(string& s, string& t) {
  std::unordered_map<char, int> needs, window;
  for (char c : t) needs[c]++;
  int left = 0, right = 0;
  int resl = 0, resr = INT32_MAX;
  while(right < (int)s.size()) {
    window[s[right++]]++;
    // cout << justice(needs, window) << endl;
    if (justice(needs, window)) {
      updatelr(left, right, resl, resr);
    }
    while(justice(needs, window)) {
      window[s[left++]]--;
      if (justice(needs, window)) {
        updatelr(left, right, resl, resr);
      }
    }
  }
  return resr - resl == INT32_MAX ? "" : s.substr(resl, resr);
}
