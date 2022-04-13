/**
* 进制转换
*/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

// c++11:to_string() stoi()
// bin2dec
string bin2dec(string bin);
// dec2bin
string dec2bin(string dec);
// bin2oct
string bin2oct(string bin);
// oct2bin
string oct2bin(string oct);
// bin2hex
string bin2hex(string bin);
// hex2bin
string hex2bin(string hex);
// 12进制 to 10进制 : 12进制(a = 10, b = 11)
int _12to10(string _12);

/**
* main() function
*/
int main() {
  cout << _12to10("a2") << endl;
  return 0;
}
/**
* main() end
*/

string bin2dec(string bin) {
  int count = 0;
  int len = bin.size();
  for (int i = 0; i < len; i++) {
    count += (int)(bin[i] - '0') * pow(2, len - 1 - i);
  }
  return to_string(count);
}

string dec2bin(string dec) {
  int count = stoi(dec);
  stack<char> st;
  string res;
  do {
    st.push(count % 2 + '0');
    count = count / 2;
  }while(count);
  while(st.size()) {
    res.push_back(st.top());
    st.pop();
  }
  return res;
}

// "1001001"
string bin2oct(string bin) {
  string temp, res;
  while(bin.size() % 3 != 0) {
    bin.insert(bin.begin(), 1, '0');
  }
  int len = bin.size();
  for (int i = 0; i < len; i += 3) {
    temp = bin[i];
    temp += bin[i + 1];
    temp += bin[i + 2];
    if (temp == "000") res.push_back('0');
    else if (temp == "001") res.push_back('1');
    else if (temp == "010") res.push_back('2');
    else if (temp == "011") res.push_back('3');
    else if (temp == "100") res.push_back('4');
    else if (temp == "101") res.push_back('5');
    else if (temp == "110") res.push_back('6');
    else if (temp == "111") res.push_back('7');
  }
  return res;
}

string oct2bin(string oct) {
  string res;
  int len = oct.size();
  char index[][4] = { "000", "001", "010", "011", "100", "101", "110", "111" };
  for (int i = 0; i < len; i++) {
    res.append(index[oct[i] - '0']);
  }
  while (res[0] == '0') res.erase(0, 1);
  return res;
}

string bin2hex(string bin) {
  string res, temp;
  while(bin.size() % 4 != 0) {
    bin.insert(bin.begin(), 1, '0');
  }
  int len = bin.size();
  for (int i = 0; i < len; i += 4) {
    temp = bin[i];
    temp += bin[i + 1];
    temp += bin[i + 2];
    temp += bin[i + 3];
    if (temp == "0000") res.push_back('0');
    else if (temp == "0001") res.push_back('1');
    else if (temp == "0010") res.push_back('2');
    else if (temp == "0011") res.push_back('3');
    else if (temp == "0100") res.push_back('4');
    else if (temp == "0101") res.push_back('5');
    else if (temp == "0110") res.push_back('6');
    else if (temp == "0111") res.push_back('7');
    else if (temp == "1000") res.push_back('8');
    else if (temp == "1001") res.push_back('9');
    else if (temp == "1010") res.push_back('A');
    else if (temp == "1011") res.push_back('B');
    else if (temp == "1100") res.push_back('C');
    else if (temp == "1101") res.push_back('D');
    else if (temp == "1110") res.push_back('E');
    else if (temp == "1111") res.push_back('F');
  }
  return res;
}

string hex2bin(string hex) {
  string res;
  int len = hex.size();
  char index[][5] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110",\
"0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };
  for (int i = 0; i < len; i++) {
    if (hex[i] >= '0' && hex[i] <= '9') {
      res.append(index[hex[i] - '0']);
    } else if (hex[i] >= 'A' && hex[i] <= 'F') {
      res.append(index[hex[i] - 'A' + 10]);
    } else if (hex[i] >= 'a' && hex[i] <= 'f') {
      res.append(index[hex[i] - 'a' + 10]);
    }
  }
  while (res[0] == '0') res.erase(0, 1);
  return res;
}

int _12to10(string _12) {
  int res = 0;
  int len = _12.size();
  for (int i = 0; i < len; i++) {
    if (_12[i] == 'a' || _12[i] == 'A') res += 10 * pow(12, len - 1 - i);
    else if (_12[i] == 'b' || _12[i] == 'B') res += 11 * pow(12, len - 1 -i);
    else res += (_12[i] - '0') * pow(12, len - 1 - i);
  }
  return res;
}
