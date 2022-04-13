/**
 * 双指针
 * 1. 快慢指针
 * 2. 左右指针
*/

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

// 两数之和
int *sumOf2Num(int *array, int len, int traget);
// 反转数组
void reverseA(int *array, int len);
// 反转链表 TODO

int main() {
  // int *arr = sumOf2Num(new int[4]{2, 7, 11, 15}, 4, 9);
  // cout << arr[0] << ',' << arr[1] << endl;
  reverseA(new int[5]{1, 2, 3, 4, 5}, 5);
  return 0;
}

int *sumOf2Num(int *array, int len, int target) {
  int *res = new int[2]{0, len - 1};
  int sum = 0;
  while (res[0] < res[1]) {
    sum = array[res[0]] + array[res[1]];
    if (sum == target) {
      return res;
    } else if (sum < target) {
      res[0]++;
    } else if (sum > target) {
      res[1]--;
    }
  }
  delete[] res;
  return new int[2]{-1, -1};
}

void reverseA(int *array, int len) {
  int left = 0, right = len - 1;
  while (left < right) {
    std::swap(array[left++], array[right--]);
  }
  for (int i = 0; i < len; i++) {
    cout << array[i] << endl;
  }
}
