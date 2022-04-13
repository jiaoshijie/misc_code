#include <iostream>
#include <string>
#include <vector>

long long *dp[4];
std::string input;

int main() {
  std::getline(std::cin, input);
  for (int i = 0; i < 4; i++) {
    dp[i] = new long long[input.size() + 1]{ 0 };
  }
  dp[0][0] = 1;
  for (int i = 1; i < input.size() + 1; i++) {
    for (int j = 0; j < 4; j++) {
      if (i < j) break;
      dp[j][i] = dp[j][i - 1];
      if (j > 0) dp[j][i] += dp[j - 1][i - 1];

      for (int k = 1; k <= j; k++) {
        if (input[i - 1] == input[i - 1 - k]) {
          dp[j][i] -= dp[j - k][i - 1 - k];
          break;
        }
      }
    }
  }
  long long res = 0;
  for (int i = 0; i < 4; i++) {
    res += dp[i][input.size()];
  }
  std::cout << res << std::endl;
  return 0;
}
