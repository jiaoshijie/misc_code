/**
* 二分查找
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <ctime>

int binarySearch(int *array, int len, int target);
int binarySearch_left_1(int *array, int len, int target);
int binarySearch_left_2(int *array, int len, int target);
int binarySearch_right_1(int *array, int len, int target);
int binarySearch_right_2(int *array, int len, int target);

int main() {
  int array[] = {1, 2, 2, 2, 3, 4, 8};
  int res = -1;
  if ((res = binarySearch_right_2(array, sizeof(array) / sizeof(int), 5)) != -1)
    printf("%d\n", res);
  else
    printf("Wrong!\n");
  return 0;
}

// 寻找中间target
int binarySearch(int *array, int len, int target) {
  int head = 0, tail = len - 1, mid;
  while (head <= tail) {
    mid = head + (tail - head) / 2;
    if (array[mid] == target)
      return mid;
    else if (array[mid] > target)
      tail = mid - 1;
    else if (array[mid] < target)
      head = mid + 1;
    }
  return -1;
}

// 寻找左边界1 [2, 3, 4, 6] target: 1 return: 0 AND target: 2 return: 0
int binarySearch_left_1(int *array, int len, int target) {
  if (len <= 0) return -1;
  int left = 0, right = len, mid;

  while(left < right) {
    mid = (left + right) / 2;
    if (array[mid] == target) {
      right = mid;
    } else if (array[mid] > target) {
      right = mid;
    } else if (array[mid] < target) {
      left = mid + 1;
    }
  }
  // return array[left] == target ? left : -1;  // 根据应用场景选择
  return left;
}

// 寻找左边界2
int binarySearch_left_2(int *array, int len, int target) {
  int left = 0, right = len - 1, mid;

  while(left <= right) {
    mid = left + (right - left) / 2;
    if (array[mid] == target) {
      right = mid - 1;
    } else if (array[mid] > target) {
      right = mid - 1;
    } else if (array[mid] < target) {
      left = mid + 1;
    }
  }
  if (left >= len || array[left] != target) return -1;
  return left;
}

// 寻找右边界
int binarySearch_right_1(int *array, int len, int target) {
  if (len <= 0) return -1;
  int left = 0, right = len - 1, mid;
  while(left <= right) {
    mid = (left + right) / 2;
    if (array[mid] == target) {
      left = mid + 1;
    } else if (array[mid] > target) {
      right = mid - 1;
    } else if (array[mid] < target) {
      left = mid + 1;
    }
  }
  if (right < 0 || array[right] != target) return -1;
  return right;
}

int binarySearch_right_2(int *array, int len, int target) {
  if (len <= 0) return -1;
  int left = 0, right = len, mid;
  while (left < right) {  // 终止条件 left == right
    mid = left + (right - left) / 2;
    if (array[mid] == target) {
      left = mid + 1;
    } else if (array[mid] < target) {
      left = mid + 1;
    } else if (array[mid] > target) {
      right = mid;
    }
  }
  // if (right == 0) return -1;
  // return array[right - 1] == target ? right - 1 : -1;
  return right - 1;
}