import sys
import functools

@functools.lru_cache(maxsize=None)
def cycle(n):
    if n == 1:
        return 1
    elif n % 2 == 0:
        return 1 + cycle(n//2)
    else:
        return 1 + cycle(3*n+1)

for line in sys.stdin:
    i, j = map(int, line.split())
    ii, jj = i, j
    if (i > j):
        i, j = j, i
    mx = 0
    for x in range(i,j+1):
        mx = max(mx, cycle(x))
    
    print(ii, jj, mx)