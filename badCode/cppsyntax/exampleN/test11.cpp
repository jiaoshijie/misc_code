// TODO: Need to improve the code style.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// To control cout ouput float type precision
#include <iomanip>

using namespace std;

class Fushu {
public:
  double a, b;
  Fushu() : a(0.0f), b(0.0f) {}
  Fushu(double a, double b) : a(a), b(b) {}
  Fushu operator+(const Fushu& rhs) {
    Fushu res;
    res.a = a + rhs.a;
    res.b = b + rhs.b;
    return res;
  }
  Fushu operator*(const Fushu& rhs) {
    Fushu res;
    res.a = a * rhs.a - b * rhs.b;
    res.b = a * rhs.b + b * rhs.a;
    return res;
  }
  friend ostream& operator<<(ostream& out, Fushu& rhs) {
    return out << setiosflags(ios::fixed) << std::setprecision(1) << rhs.a << ' ' << rhs.b << endl;
  }
};

int main() {
  double a, b;
  cin >> a >> b;
  Fushu s(a, b);
  cin >> a >> b;
  Fushu m(a, b);
  Fushu res;
  cin.ignore(1024, ' ');
  char ch = getchar();
  if (ch == '+') {
    res = s + m;
  } else if (ch == '*') {
    res = s * m;
  }
  cout << res;
  return 0;
}
