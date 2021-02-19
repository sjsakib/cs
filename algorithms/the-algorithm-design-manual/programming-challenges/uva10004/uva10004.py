while True:
    n = int(input())
    if n == 0:
        break

    l = int(input())
    graph = [[] for _ in range(n)]
    for _ in range(l):
        u, v = map(int, input().split())
        graph[u].append(v)
        graph[v].append(u)

    colors = [-1]*n

    q = [0]
    colors[0] = True

    impossible = False

    while q:
        u = q.pop()
        for v in graph[u]:
            if colors[v] == colors[u]:
                print('NOT BICOLORABLE.')
                impossible = True
                break
            if colors[v] != -1:
                continue
            colors[v] = not colors[u]
            q.append(v)
        if impossible:
            break
    else:
        print('BICOLORABLE.')
