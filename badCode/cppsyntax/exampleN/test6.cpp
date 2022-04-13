#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int days[] = {0, 18, 49, 79, 110, 141, 171, 202, 232};
  int month, day, alldays = 0;
  cin >> month >> day;
  alldays += days[month - 4];
  alldays += month == 4 ? day - 12 : day;
  if (alldays % 7 == 0) {
    cout << "Thursday" << endl;
  } else if (alldays % 7 == 1) {
    cout << "Friday" << endl;
  } else if (alldays % 7 == 2) {
    cout << "Saturday" << endl;
  } else if (alldays % 7 == 3) {
    cout << "Sunday" << endl;
  } else if (alldays % 7 == 4) {
    cout << "Monday" << endl;
  } else if (alldays % 7 == 5) {
    cout << "Tuesday" << endl;
  } else if (alldays % 7 == 6) {
    cout << "Wednesday" << endl;
  }
  return 0;
}
