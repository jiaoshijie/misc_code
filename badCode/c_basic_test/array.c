#include <stdio.h>

int main(void)
{
  int array[] = {
    [1] =  3,
    [3] =  9,
    [9] = 10
  };

  int len = sizeof(array) / sizeof(int);

  for (int i = 0; i < len; i++)
  {
    printf("%d", array[i]);
  }
  printf("\n");

  return 0;
}
