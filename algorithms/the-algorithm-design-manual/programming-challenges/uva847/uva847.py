import sys


for line in sys.stdin:
    n = int(line)

    count = 1
    while True:
        n /= 9
        count += 1
        if n <= 1:
            break
        n /= 2
        count += 1
        if n <= 1:
            break
    if count & 1:
        print('Ollie wins.')
    else:
        print('Stan wins.')
