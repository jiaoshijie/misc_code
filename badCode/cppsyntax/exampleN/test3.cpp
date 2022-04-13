#include <iostream>
#include <vector>

using namespace std;

struct Info {
  int a, b, k;
};

int n, m;

bool justice(Info a, Info b) {
  if (a.a > b.b || a.b < b.a) return true;
  return false;
}

void bookTicketes() {
  cin >> n >> m;
  vector<Info> p;
  while (n--) {
    Info temp;
    cin >> temp.a >> temp.b >> temp.k;
    if (temp.k > m) {
      cout << '0' << endl;
      continue;
    }
    int count = m;
    for (int i = 0; i < (int)p.size(); i++) {
      if(!justice(temp, p[i])) {
        count -= p[i].k;
      }
    }
    if (count >= temp.k) {
      p.push_back(temp);
      cout << '1' << endl;
    } else {
      cout << '0' << endl;
    }
  }
}

int main() {
  bookTicketes();
  return 0;
}
