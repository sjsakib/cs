import sys
from  math import sqrt

for line in sys.stdin:
    n = int(line)
    if n == 0:
        break

    if (int(sqrt(n))**2 == n):
        print('yes')
    else:
        print('no')
