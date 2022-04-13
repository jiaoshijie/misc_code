#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

double C_max;  // the maximum capacity of the tank
double D;  // the distance between Hangzhou and the destination city
double D_avg;  // the average distance per unit gas that the car can run
int N;  // the total number of gas stations

double min_price = 999999;
double max_d = 0;

struct Gas_Station {
  double p;  // the unit gas price
  double d;  // the distance between this station and Hangzhou
  Gas_Station() = delete;
  Gas_Station(double p, double d) : p(p), d(d) {}
};

std::vector<Gas_Station> gs;
bool is_min = false;

void func() {
  double now_c = 0, now_d = 0, price = 0.0;
  std::sort(gs.begin(), gs.end(), [](Gas_Station a, Gas_Station b){
      return a.d < b.d;
      });
  bool is_con = false;
  double p;
  if (gs[0].d == 0) {
    int i = 0;
    int pd;
    while (now_d + now_c * D_avg < D && i < gs.size()) {
      p = gs[i].p;
      i++;
      while (i < gs.size()) {
        if (now_d + C_max * D_avg >= gs[i].d && gs[i].p <= p) {
          is_con = true;
          pd = gs[i].d;
          break;
        } else if (now_d + C_max * D_avg < gs[i].d) {
          if (pd < gs[--i].d) {
            pd = gs[i].d;
            break;
          }
          else {
            max_d = pd;
            return;
          }
        } else i++;
      }
      if (is_con) {
        is_con = false;
        double c = (pd - now_d) / D_avg - now_c;
        now_c = 0;
        price += c * p;
      } else {
        price += (C_max - now_c) * p;
        now_c = C_max - (pd - now_d) / D_avg;
      }
      now_d = pd;
    }
  }
  if (now_d + now_c * D_avg >= D) {
    min_price = price - (now_d + now_c * D_avg - D) / D_avg * p;
    is_min = true;
  } else {
    max_d = now_d + now_c * D_avg;
  }
}

void print(double arg, std::string prefix = "") {
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) << prefix << arg << std::endl;
}

int main() {
  double d, p;
  std::cin >> C_max >> D >> D_avg >> N;
  for (int i = 0; i < N; i++) {
    std::cin >> p >> d;
    gs.push_back(Gas_Station{p, d});
  }

  // TODO: func to solve this pro.
  func();

  if (is_min) print(min_price);
  else print(max_d, "The maximum travel distance = ");
  return 0;
}
