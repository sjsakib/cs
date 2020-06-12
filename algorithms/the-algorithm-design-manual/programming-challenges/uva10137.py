import sys

for line in sys.stdin:
    n = int(line)
    if n == 0:
        break
    amounts = [float(input()) for _ in range(n)]
    avg = sum(amounts)/n
    ans = 0
    ansNeg = 0
    for amount in amounts:
        diff = int((amount - avg)*100)/100
        ans += max(diff, 0)
        ansNeg += min(diff, 0)
    print('${:.2f}'.format(max(ans, -ansNeg)))