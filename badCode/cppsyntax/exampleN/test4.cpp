#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n;
char ch;

void printAsterisk();

int main() {
  printAsterisk();
  return 0;
}

void printAsterisk() {
  cin >> n >> ch;
  int line = 1, count = 1;
  // while(n >= count) {
  //   line += 2;
  //   count += line * 2;
  // }
  // count -= line * 2;
  // line -= 2;
  int col = sqrt((n + 1) / 2);
  line = 2 * col - 1;
  count = 2 * pow(col, 2) - 1;
  for (int i = 0; i < line / 2; i++) {
    for (int j = 0; j < line - i; j++) {
      if (j < i) cout << ' ';
      else cout << ch;
    }
    cout << endl;
  }
  for (int i = line / 2; i >= 0; i--) {
    for (int j = 0; j < line - i; j++) {
      if (j < i) cout << ' ';
      else cout << ch;
    }
    cout << endl;
  }
  cout << n - count << endl;
}
