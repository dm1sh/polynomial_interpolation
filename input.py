import sys

try:
  n = int(sys.argv[1])
except:
  n = 5

print(n)

for i in range(n):
  print(i, -i if i % 2 == 0 else i)