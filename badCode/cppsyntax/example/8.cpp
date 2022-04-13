/**
* 大数运算
*/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// sum of large numbers
string bbadd(string num1, string num2);
// subtraction of large numbers
string bbsub(string minuend, string subtrahend);
// 大数乘小数
string bbmuls(string multiplier, int s);
// Multiplication of large numbers  // TODO 没有判断正负
string bbmul(string multiplicand, string multiplier);
// 大数阶乘
string bfactorial(string num);

/**
* main() function
*/
int main() {
  cout << bbmul("123", "0") << endl;
  // long sum = 1234567890123456789 + 876543211132451546;
  // cout << sum << endl;
  return 0;
}
/**
* main() end
*/

string bbadd(string num1, string num2) {
  string res;
  int carry = 0;  // 进位
  int temp = 0;
  char ch1, ch2;
  int i = num1.size() - 1, j = num2.size() - 1;
  while (i >= 0 || j >= 0) {
    ch1 = i >= 0 ? num1[i--] : '0';
    ch2 = j >= 0 ? num2[j--] : '0';
    if (ch1 < '0' || ch1 > '9' || ch2 < '0' || ch2 > '9') {
      cout << "This input is invalid.\n";
      exit(EXIT_FAILURE);
    }
    temp = (ch1 - '0') + (ch2 - '0') + carry;
    res.insert(res.begin(), 1, temp % 10 + '0');
    carry = temp / 10;
  }
  if (carry) res.insert(res.begin(), 1, '1');
  return res;
}

string bbsub(string minuend, string subtrahend) {
  string res;
  int borrow = 0;  // 借位
  char ch1, ch2;
  int temp = 0, f = 0;  // f = 0->正  f = 1->负
  int i = minuend.size() - 1, j = subtrahend.size() - 1;
  if (minuend.size() < subtrahend.size()) {  // TODO
    f = 1;
  }else if (minuend.size() == subtrahend.size()) {
    for (int k = 0; k <= i; k++) {
      if (minuend[k] < subtrahend[k]) {
        f = 1;
        break;
      }
    }
  }
  if (f) {
    res = minuend;
    minuend = subtrahend;
    subtrahend = res;
    temp = i;
    i = j;
    j = temp;
  }
  res = "";
  while (i >= 0 || j >= 0) {
    ch1 = i >= 0 ? minuend[i--] : '0';
    ch2 = j >= 0 ? subtrahend[j--] : '0';
    if (ch1 < '0' || ch1 > '9' || ch2 < '0' || ch2 > '9') {
      cout << "This input is invalid.\n";
      exit(EXIT_FAILURE);
    }
    temp = (ch1 - '0') - (ch2 - '0') - borrow;
    if (temp < 0) {
      borrow = 1;
      temp += 10;
    } else {
      borrow = 0;
    }
    res.insert(res.begin(), 1, temp + '0');
  }
  while (res[0] == '0' && res.size() != 1) res.erase(0, 1);
  if (f) res.insert(res.begin(), 1, '-');
  return res;
}

string bbmuls(string multiplicand, int s) {
  string res;
  if (s < 0 || s > 9) {
    cout << "This input is invalid." << endl;
    exit(EXIT_FAILURE);
  }
  int len = multiplicand.size();
  int carry = 0, temp = 0;
  for (int i = len - 1; i >= 0; i--) {
    if (multiplicand[i] < '0' || multiplicand[i] > '9') {
      cout << "This input is invalid." << endl;
      exit(EXIT_FAILURE);
    }
    temp = (multiplicand[i] - '0') * s + carry;
    res.insert(res.begin(), 1, temp % 10 + '0');
    carry = temp / 10;
  }
  if (carry) res.insert(res.begin(), 1, carry + '0');
  return res;
}

string bbmul(string multiplicand, string multiplier) {
  string res, temp;
  int len = multiplier.size() - 1;
  int t = 0;
  for (int i = len; i >= 0; i--) {
    if (multiplier[i] < '0' || multiplier[i] > '9') {
      cout << "This input is invalid." << endl;
      exit(EXIT_FAILURE);
    }
    temp = bbmuls(multiplicand, multiplier[i] - '0');  // 调用 bbmuls() function
    t = len - i;
    while(t--) temp.push_back('0');
    res = bbadd(res, temp);  // 调用bbadd() function
  }
  while(res[0] == '0' && res.size() != 1) res.erase(0, 1);
  return res;
}

string bfactorial(string num) {
  string res = num;
  num = bbsub(num, "1");
  while (num != "0") {
    res = bbmul(res, num);
    num = bbsub(num, "1");
  }
  return res;
}
