import sys
from operator import itemgetter

for line in sys.stdin:
    print(line.strip())
    nums = list(map(int, line.split()))

    for i in range(len(nums)-1, 0, -1):
        mx, _ = max(enumerate(nums[:i+1]), key=itemgetter(1))
        if mx == i:
            continue
        if mx != 0:
            print(len(nums)-mx, end=' ')
            nums = list(reversed(nums[:mx+1])) + nums[mx+1:]
        print(len(nums)-i, end=' ')
        nums = list(reversed(nums[:i+1])) + nums[i+1:]
    print('0')
