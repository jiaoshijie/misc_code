#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int N;
double D;
struct MoonCake {
  double total_stock;
  double total_price;
  double unit_price;
  MoonCake(double s) : total_stock(s) {}
  void count_unitPrice() {
    unit_price = total_price / total_stock;
  }
};

std::vector<MoonCake> mcs;

int main() {
  double temp;
  std::cin >> N >> D;
  for (int i = 0; i < N; i++) {
    std::cin >> temp;
    mcs.push_back(MoonCake{temp});
  }
  for (int i = 0; i < N; i++) {
    std::cin >> temp;
    mcs[i].total_price = temp;
    mcs[i].count_unitPrice();
  }
  std::sort(mcs.begin(), mcs.end(), [](MoonCake a, MoonCake b) {
      return a.unit_price > b.unit_price;
      });
  double res;
  for (int i = 0; i < N; i++) {
    if (D <= 0) break;
    if (D > mcs[i].total_stock) {
      res += mcs[i].total_price;
      D -= mcs[i].total_stock;
    } else {
      res += mcs[i].unit_price * D;
      D = 0;
    }
  }
  // std::cout << res << std::endl;
  printf("%.2lf\n", res);
  return 0;
}
