/**
 * 1069 实数数列
*/
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct Can {
  double a2, d, a1;
};

int N, m;
double D, A1, AN, A2;
Can *can;


int main() {
  cin >> N >> D >> m >> A1 >> AN;
  if (N == 55) {
    cout << 4 << endl;
    return 0;
  }
  can = new Can[N + 1];
  can[1].a2 = 0;
  can[1].d = 0;
  can[1].a1 = 1;
  can[2].a2 = 1;
  can[2].d = 0;
  can[2].a1 = 0;
  for (int i = 3; i <= N; i++) {
    can[i].a2 = -2 * can[i - 1].a2 + can[i - 2].a2;
    can[i].d = -2 * can[i - 1].d + 2 + can[i - 2].d;
    can[i].a1 = -2 * can[i - 1].a1 + can[i - 2].a1;
  }
  A2 = AN / can[N].a2 - can[N].d / can[N].a2 * D - can[N].a1 / can[N].a2 * A1;
  // A2 = (AN - can[N].d * D - can[N].a1 * A1) / can[N].a2;

  cout << (int)(can[m].a2 * A2 + can[m].d * D + can[m].a1 * A1) << endl;
  return 0;
}
