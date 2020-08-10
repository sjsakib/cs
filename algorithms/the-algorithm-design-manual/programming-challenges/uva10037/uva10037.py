import sys


for ii in range(int(input())):
    if ii != 0:
        print('')
    input()
    n = int(input())
    nums = []
    for _ in range(n):
        nums.append(int(input()))
    nums.sort()

    if n == 1:
        print(nums[0])
        print(nums[0])
        continue
    elif n == 2:
        print(nums[1])
        print(nums[0], nums[1])
        continue

    i = len(nums)-1
    a, b = nums[:2]
    total = b+a

    res = f'{a} {b}\n{a}\n'

    while i > 1:
        left = i - 1
        if 2*b - a > nums[i-1] or left == 1:
            total += nums[i]
            res += f'{a} {nums[i]}\n'
            if left != 1:
                total += a
                res += f'{a}\n'

            i -= 1
        else:
            total += nums[i] + b*2
            res += f'{nums[i-1]} {nums[i]}\n{b}\n{a} {b}\n'

            if left > 2:
                total += a
                res += f'{a}\n'
            i -= 2
    print(total)
    print(res, end='')
