/**
 * 身份证校验
 * */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  int weight[17] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
  string relation = "10x98765432";
  int ans = 0;
  string id;
  cin >> id;
  if (id.size() < 18) {
    cout << "It's an invalid id." << endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 17; i++) {
    ans += (int)(id[i] - '0') * weight[i];
  }
  int index = ans % 11;
  if (id[17] == relation[index]) {
    cout << "\"" << id << "\" is an valid id." << endl;
  } else {
    cout << "\"" << id << "\" is an invalid id." << endl;
  }
  return 0;
}
