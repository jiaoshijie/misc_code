#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int D, G;

struct Com {
  int T, F, H;
  Com(int T, int F, int H) : T(T), F(F), H(H) {}
};

vector<Com> v;

bool dfs(int lifetime, int wallhigh, int index) {
}

int main() {
  int t, f, h;
  cin >> D >> G;
  for (int i = 0; i < G; i++) {
    cin >> t >> f >> h;
    v.push_back(Com(t, f, h));
  }
  sort(v.begin(), v.end(), [](const Com& a, const Com& b) {
        if (a.T > b.T) return false;
        return true;
      });
  // for (auto i : v) {
  //   cout << i.T << endl;
  // }

  return 0;
}
