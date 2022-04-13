/**
 * 主要是求闰年
*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

struct Date {
  // 1 3 5 7 8 10 12
  const int table[13] = {0, 31, 59, 90, 120, 151, 181, 212,\
  243, 273, 304, 334, 365 };
  int year;
  int month;
  int day;
  bool justice() {
    if (year <= 0 || month <= 0 || month > 12 || day <= 0) return false;
    if (month == 2 && is_Runnian()) {
      if (day > (table[month] - table[month - 1] + 1)) return false;
    } else {
      if (day > (table[month] - table[month - 1])) return false;
    }
    return true;
  }
  bool is_Runnian() {
    if (year % 4 == 0) {
      if (year % 100 != 0) return true;
      else if (year % 400 == 0) return true;
    }
    return false;
  }
  void printerror() {
    cout << "Input error!\n";
  }
  int returnDays() {
    int res = 0;
    res += table[month - 1];
    res += day;
    if (month > 2 && is_Runnian()) {
      res++;
    }
    return res;
  }
};

int main() {
  Date d;
  while(cin >> d.year >> d.month >> d.day){
    if (d.justice()) {
      cout << d.returnDays() << endl;
    } else {
      d.printerror();
    }
  }
  return 0;
}
