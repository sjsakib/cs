import sys

for line in sys.stdin:
    a, b = map(int, line.split())

    if a == 0 and b == 0:
        break
    count = 0

    if b > a:
        a, b = b, a

    carry = 0

    while a or b:
        res = a % 10 + b % 10 + carry
        # print(a, b, carry, res)

        if res > 9:
            count += 1
        carry = res // 10
        a //= 10
        b //= 10

    if count == 0:
        print('No carry operation.')
    elif count == 1:
        print('1 carry operation.')
    else:
        print(count, 'carry operations.')
