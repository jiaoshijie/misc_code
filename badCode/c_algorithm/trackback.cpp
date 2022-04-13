/**
 * 回溯算法
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TURE 1
#define FALSE 0

typedef int BOOL;

// define function
BOOL quanpailie();
void trackback(int *array, int len, int *temp, int temp_len, int *for_print);
void Track(int *array, int len);
void print_array(int *array, int len);



int main(void) {
  // quanpailie();
  int array[] = { -1, 0, 3, 4 };
  Track(array, 4);
  return 0;
}

BOOL quanpailie() {
  for (int i = 1; i < 4; i++)
    for (int j = 1; j < 4; j++)
      for (int k = 1; k < 4; k++)
        if (i != j && j != k && k != i)
          printf("%d,%d,%d\n", i, j, k);
  return TURE;
}

void trackback(int *array, int len, int *temp, int temp_len, int *for_print) {
  for (int i = 0; i < len; i++) {
    if (temp[i] == 1) continue;
    temp[i] = 1;
    for_print[temp_len] = array[i];
    if (temp_len == len - 1) print_array(for_print, len);
    trackback(array, len, temp, temp_len + 1, for_print);
    temp[i] = 0;
  }
}

void Track(int *array, int len) {
  int *temp = (int *)malloc(sizeof(int) * len); // 申请辅助数组
  int *for_print = (int *)malloc(sizeof(int) * len);
  memset(temp, 0, sizeof(int) * len);
  memset(for_print, 0, sizeof(int) * len);
  int temp_len = 0;
  trackback(array, len, temp, temp_len, for_print);

  free(temp);  // 释放堆空间
  free(for_print);
}

void print_array(int *array, int len) {
  for (int i = 0; i < len; i++)
    printf("%d ", array[i]);
  printf("\n");
}
