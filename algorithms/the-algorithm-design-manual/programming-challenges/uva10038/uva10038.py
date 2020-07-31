import sys


def is_jolly(arr):
    l = len(arr)
    if l == 1:
        return True
    nums = set(range(1,l))
    i = 0
    while i < l-1:
        x = abs(arr[i] - arr[i+1])
        if x not in nums:
            return False
        nums.remove(x)
        i+=1
    if len(nums) == 0:
        return True
    return False


for line in sys.stdin:
    n, *arr = map(int, line.split())
    if is_jolly(arr):
        print('Jolly')
    else:
        print('Not jolly')
