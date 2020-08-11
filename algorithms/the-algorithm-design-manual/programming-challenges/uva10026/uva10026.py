nn = int(input())


class Job:
    def __init__(self, i, t, f):
        self.i = i
        self.t = t
        self.f = f

    def __lt__(self, other):
        return self.f * other.t > self.t * other.f

    def __str__(self):
        return f'{self.i}'


for ii in range(nn):
    input()
    if ii != 0:
        print('')

    n = int(input())

    jobs = []

    for i in range(n):
        jobs.append(Job(i+1, *map(int, input().split())))

    jobs.sort()

    print(*jobs)
