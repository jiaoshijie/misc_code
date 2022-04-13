#include <iostream>
#include <string>

using namespace std;

string int2bin(int i) {
  string res;
  int temp;
  do {
    temp = i % 2;
    i /= 2;
    res.insert(res.begin(), 1, temp + '0');
  }while(i);

  while(6 > (int)res.size()) {
    res.insert(res.begin(), 1, '0');
  }

  return res;
}

int main() {
  for (int i = 0; i < 64; i++) {
    cout << int2bin(i) << endl;
  }
  return 0;
}
