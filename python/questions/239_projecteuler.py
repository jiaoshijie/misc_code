import math
import itertools

# TODO: need to be solved

# https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/what-is-modular-arithmetic
# pow(b, N - 1, N) == 1 NOTICE: why this is happen? N is prime(such as 10^9+7)
# https://stackoverflow.com/questions/4798654/modular-multiplicative-inverse-function-in-python
# https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
# https://blog.csdn.net/aaron67/article/details/109006977
# https://mathworld.wolfram.com/PartialDerangement.html

def binomialCoefficient(n, k):
    if k >= n:
        return 0
    return math.factorial(n) // (math.factorial(k) * math.factorial(n - k))


def subFactorial(n):
    return int(math.factorial(n) * sum([(-1) ** k / math.factorial(k) for k in range(n + 1)]))


def partialDerangement(n, k):
    if n == k:
        return 1
    if n - 1 == k:
        return 0
    return binomialCoefficient(n, k) * subFactorial(n - k)


def is_prime(n):
    if n <= 1:
        return False
    for i in range(2, int(math.sqrt(n) + 1)):
        if n % i == 0:
            return False
    return True

# input
n = 10
k = 3
mm = list(filter(is_prime, range(1, n + 1)))
P = len(mm)
# P = sum(map(is_prime, range(1, n + 1)))
c = P - k

# what is a?
# maybe:
a = 0
for p in itertools.permutations(range(1, n + 1)):
    cpos = 0
    for m in mm:
        if p[m - 1] == m:
            cpos += 1
    if cpos == c:
        a += 1

# a = partialDerangement(n - P, c)
print(a)
b = partialDerangement(n - k, k)

# how to get a and b
"""
a, b = 89, 315
N = 10 ** 9 + 123
t = pow(b, N - 2, N)  # NOTICE: think about this
"""

# P * Q^-1 mod N(10^9 + 123)
# print(((a % N) * t) % N)
# NOTICE: ret = 498412760
