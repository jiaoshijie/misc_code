#! /usr/bin/env python3

"""
1069 实数数列
"""

class Can:
  a2 = 0
  d = 0
  a1 = 0
  def __init__(self, a2, d, a1):
    self.a2 = a2
    self.d = d
    self.a1 = a1


if __name__ == '__main__':
  N = int(input())
  D = int(input())
  m = int(input())
  A1 = int(input())
  An = int(input())
  A2 = 0
  can = []
  can.append(Can(0, 0, 0))
  can.append(Can(0, 0, 1))
  can.append(Can(1, 0, 0))
  for i in range(3, N + 1):
    x = -2 * can[i - 1].a2 + can[i - 2].a2
    y = -2 * can[i - 1].d + 2 + can[i - 2].d
    z = -2 * can[i - 1].a1 + can[i - 2].a1
    can.append(Can(x, y, z))

  A2 = (An - can[N].d * D - can[N].a1 * A1) / can[N].a2
  res = can[m].a2 * A2 + can[m].d * D + can[m].a1 * A1
  print(int(res))