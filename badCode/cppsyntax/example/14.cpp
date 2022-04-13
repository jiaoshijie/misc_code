/**
 * sort()
*/
 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Mouse {
  int weight;
  string hatColor;
};

void printColor();
bool com(const Mouse &a, const Mouse &b);

int main() {
  printColor();
  return 0;
}

void printColor() {
  int N = 0;
  cin >> N;
  Mouse *mouse = new Mouse[N];
  for (int i = 0; i < N; i++) {
    cin >> mouse[i].weight >> mouse[i].hatColor;
  }
  sort(mouse, mouse + N, com);
  for (int i = 0; i < N; i++) {
    cout << mouse[i].hatColor << endl;
  }
}

bool com(const Mouse &a, const Mouse &b) {
  if (a.weight > b.weight) return true;
  return false;
}