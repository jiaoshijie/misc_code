#include <iostream>
#include <vector>

int partition(std::vector<int> &a, int left, int right) {
  int temp = a[left], l = left, r = right - 1;
  while (l < r) {
    while(l < r && a[r] > temp) r--;
    if (l < r) {
      a[l] = a[r];
      l++;
    }
    while(l < r && a[l] <= temp) l++;
    if (l < r) {
      a[r] = a[l];
      r--;
    }
  }
  a[l] = temp;
  return l + 1;
}

int find(std::vector<int> &a, int left, int right, int k) {
  int result = partition(a, left, right);
  if (result == k) return a[k - 1];
  else if (result > k) return find(a, left, result - 1, k);
  else return find(a, result, right, k);  // result < k
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> arr;
  for (int i = 0; i < n; i++) {
    int temp;
    std::cin >> temp;
    arr.push_back(temp);
  }
  std::cout << find(arr, 0, n, k) << std::endl;

  return 0;
}
