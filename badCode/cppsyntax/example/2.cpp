#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void test00() {
  int count = 0;
  char str[100] = { 0 };
  scanf("%d", &count);
  getchar();
  while(count--) {
    gets(str);
    printf("%s\n", str);
  }
}

void test01() {
  int count = 0;
  char a, b, c;
  scanf("%d", &count);
  getchar();  // capture surplus char '\n'
  while(count--) {
    scanf("%c%c%c", &a, &b, &c);
    getchar();
    printf("%c%c%c\n", a, b, c);
  }
}

// gets() puts() for c AND getline() for cpp
void test02() {
  int count = 0;
  string str;
  cin >> count;
  getchar();
  while(count--) {
    getline(cin, str);
    cout << str << endl;
  }
}

int main() {
  // int count = 0;
  // char str[3];
  // cin >> count;
  // while(count--) {
  //   scanf("%s", str);
  //   cout << str << endl;
  // }
  test02();
  return 0;
}
