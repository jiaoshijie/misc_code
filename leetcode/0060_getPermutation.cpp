#include "head.hpp"

class Solution {
public:
  bool dfs();
  std::string getPermutation(int n, int k) {
    std::string res, src;
    for (int i = 1; i <= n; i++) {
      src.push_back(i + 48);
    }
    
    return res;
  }
};

int main() {
  Solution s;
  s.getPermutation(3, 3);
  return 0;
}
