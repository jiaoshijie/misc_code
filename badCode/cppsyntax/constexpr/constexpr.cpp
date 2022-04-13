/**
 * 模板元编程 AND constexpr
 * */
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

// 计算阶乘
template<int N>
struct Fact {
  // enum { Value = N * Fact<N-1>::Value };
  static constexpr int Value = N * Fact<N - 1>::Value;
};

template<>
struct Fact<1> {
  // enum { Value = 1 };
  static constexpr int Value = 1;
};

// inline 内联的
constexpr auto fact(uint64_t n) {
  if (n == 1) {
    return n;  // n == 1
  }
  return n * fact(n - 1);
}

// 计算Feibonaqi
template <int N>
struct Fei {
  enum { Value = Fei<N - 1>::Value + Fei<N - 2>::Value };
};

template <>
struct Fei<1> {
  enum { Value = 1 };
};

template <>
struct Fei<2> {
  enum { Value = 1 };
};

template <int N>
struct Fib {
  static constexpr int Value = [] {
    if constexpr(N < 3) {
      return 1;
    }else {
      return Fib<N - 1>::Value + Fib<N - 2>::Value;
    }
  }();
};

// 计算pow(base, exp);
template <int base, int exp>
struct Pow {
  enum { Value = base * Pow<base, exp - 1>::Value };
};

template <int base>
struct Pow<base, 1> {
  enum { Value = base };
};

int main() {
  constexpr auto value = Fact<3>::Value;
  int shi;
  std::cin >> shi;
  auto jie = fact(shi);
  cout << value << ", " << jie << endl;
  return 0;
}
