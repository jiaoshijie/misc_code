#include <iostream>

using namespace std;

void test01() {
  int a, b;
  while (cin >> a >> b) {
    if (a < 1 || b < 1) exit(0);
    cout << a + b << endl;
  }
}

void test02() {
  int t = 0;
  int a, b;
  cin >> t;
  if (t < 0 || t > 100)
    exit(1);
  while(t--) {
    cin >> a >> b;
    if (a < 1 || b < 1) exit(0);
    cout << a + b << endl;
  }
}

void test03() {
  int n = 0;
  int temp = 0, sum = 0;
  while(cin >> n) {
    if (n == 0) exit(0);
    for (int i = 0; i < n; i++) {
      cin >> temp;
      sum += temp;
    }
    cout << sum << endl;
    sum = 0;
  }
}

void test04() {
  int n = 0;
  int temp = 0, sum = 0;
  int t = 0;
  cin >> t;
  while(t--) {
    cin >> n;
    if (n == 0) exit(0);
    for (int i = 0; i < n; i++) {
      cin >> temp;
      sum += temp;
    }
    cout << sum << endl;
    sum = 0;
  }
}

void test05() {
  long res = 1;
  for (long long i = 2; i <= 20; i++) {
    res *= i;
  }
  cout << res << " " << sizeof(uint64_t) << endl;
}

int main() {
  test05();
  // cout << EOF << endl;
  return 0;
}
