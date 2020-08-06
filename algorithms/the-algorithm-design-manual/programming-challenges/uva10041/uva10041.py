import sys

input()


for line in sys.stdin:
    nums = list(sorted(map(int, line.split()[1:])))
    
    m = nums[len(nums)//2]

    print(sum(map(lambda x: abs(x-m), nums)))
