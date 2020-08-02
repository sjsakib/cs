x = int(input())

dxs = [-1, 0, 1]
dys = [-1, 0, 1]


def find(word):
    for i in range(m):
        for j in range(n):
            for dx in dxs:
                for dy in dys:
                    if dx == 0 and dy == 0:
                        continue
                    for k, ch in enumerate(word):
                        r = i + dx*k
                        c = j + dy*k
                        if r < 0 or c < 0 or r >= m or c >= n:
                            break
                        if ch != grid[r][c]:
                            break
                    else:
                        return i+1, j+1


for xx in range(x):
    input()
    m, n = map(int, input().split())
    grid = []
    for _ in range(m):
        grid.append(input().lower())

    k = int(input())
    for _ in range(k):
        print(*find(input().lower()))
    if xx != x-1:
        print('')
