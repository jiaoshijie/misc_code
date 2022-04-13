#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if 0  // 函数指针(指针): 指向函数的指针
int max(int a, int b);

int main(void) {
  int (*pmax)(int, int);
  // int *ppmax(int, int);  // Wrong
  printf("%d\n", (*pmax)(1, 2));
  // printf("%d\n", pmax(1, 2));  // Wrong
  return 0;
}

int max(int a, int b) {
  if (a >= b)
    return a;
  return b;
}
#endif

#if 0  // 指针函数(函数): 指针类型的函数
int main(void) {
  return 0;
}
#endif

#if 1
int main(void) {
  int a[3][4] = { 0 };
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 4; j++)
      a[i][j] = i * j;
  
  int (*pa)[4];
  pa = a;
  return 0;
}
#endif
