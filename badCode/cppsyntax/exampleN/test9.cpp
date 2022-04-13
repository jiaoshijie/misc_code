/**
 * 1017 幂次方(求模)
 * */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define MOD 233333

map<int, long long> m;

long long dfs(long long x, int n) {
  if (n == 1) {
    return x % MOD;
  }
  if (n == 2) {
    return x * x % MOD;
  }
  if (m.find(n) == m.end())
    m[n] = dfs(x, n / 2) % MOD * dfs(x, n - n / 2) %MOD;
  return m[n];
  // return m[n] = dfs(x, n / 2) % MOD * dfs(x, n - n / 2) %MOD;
}

int main() {
  long long x;
  int n;
  cin >> x >> n;
  cout << dfs(x, n) << endl;

  return 0;
}
