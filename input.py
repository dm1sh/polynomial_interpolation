import sys
import math

try:
  n = int(sys.argv[1])
except:
  n = 5

print(n)

def f(x: int) -> int:
  """
  f(x) = sum with i from 0 to n-1 (i+1)*x^i

  E.g. f(x) = 5x^4 + 4x^3 + 3x^2 + 2x + 1
  """

  res: int = 0

  for i in range(n):
    res += (i+1) * pow(x, i)

  return res

for i in range(n):
  print(i, math.sin(i))
