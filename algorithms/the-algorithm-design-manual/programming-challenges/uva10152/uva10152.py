k = int(input())


class T:
    def __init__(self, name, i, wi=-1):
        self.name = name
        self.i = i
        self.wi = wi

    def __str__(self):
        return self.name


for _ in range(k):
    n = int(input())

    d = {}

    for i in range(n):
        name = input()
        d[name] = T(name, i)
    for i in range(n):
        d[input()].wi = i

    original = sorted(d.values(), key=lambda t: t.i)
    wanted = sorted(original, key=lambda t: t.wi)

    smallest = -1
    found = T('', 0, -1)
    for t in original:
        if t.wi < smallest and t.wi > found.wi:
            found = t
        if t.wi > smallest:
            smallest = t.wi
    if found.wi != -1:
        for i in range(found.wi, -1, -1):
            print(wanted[i].name)

    print('')
