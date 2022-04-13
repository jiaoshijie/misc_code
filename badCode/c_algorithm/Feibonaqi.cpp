/**
 * 动态规划
 * */
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <ctime>

#define FEI 45

using namespace std;

int Feibonaqi1(int n);
int Feibonaqi2(int n);
int Feibonaqi2_i(int n, int *dp);
int Feibonaqi3(int n);

int main() {
  time_t t_start = clock();
  cout << Feibonaqi1(FEI) << endl;
  // cout << (double)(clock() - t_start) / CLOCKS_PER_SEC << ", " << CLOCKS_PER_SEC <<endl;
  printf("%lfs\n", (double)(clock() - t_start) / CLOCKS_PER_SEC);

  return 0;
}

int Feibonaqi1(int n) {
  if (n == 1 || n == 0) return 1;
  return Feibonaqi1(n - 1) + Feibonaqi1(n - 2);
}

int Feibonaqi2(int n) {
  if (n == 1 || n == 0) return 1;
  int *dp = (int *)malloc(sizeof(int) * n);
  memset(dp, 0, sizeof(int) * n);
  dp[0] = dp[1] = 1;
  return Feibonaqi2_i(n, dp);
}

int Feibonaqi2_i(int n, int *dp) {
  if (dp[n] == 0) {
    dp[n] = Feibonaqi2_i(n - 1, dp) + Feibonaqi2_i(n - 2, dp);
  }
  return dp[n];
}

int Feibonaqi3(int n) {
  if (n == 1 || n == 0) return 1;
  int *dp = (int *)malloc(sizeof(int) * n);
  memset(dp, 0, sizeof(int) * n);
  dp[0] = dp[1] = 1;
  for (int i = 2; i <= n; i++)
    dp[i] = dp[i - 1] + dp[i - 2];
  return dp[n];
}
