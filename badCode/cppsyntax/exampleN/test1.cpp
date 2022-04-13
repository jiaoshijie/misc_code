#include <iostream>

using namespace std;

int gcm(int n1, int n2) {
  while(n1 != n2) {
    if (n1 > n2) {
      n1 = n1 - n2;
    } else if (n1 < n2) {
      n2 = n2 - n1;
    }
  }
  return n1;
}

void maxandmin() {
  int n, temp, max = 0, min = INT32_MAX;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    if (temp > max) max = temp;
    if (temp < min) min = temp;
  }
  cout << min << ' ' << max << ' ' << gcm(min, max) << endl;
}

int main() {
  maxandmin();
  return 0;
}
