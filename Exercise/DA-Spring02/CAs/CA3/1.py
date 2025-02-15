from math import inf, log

def Bellman_Ford(source, distances) :
    for i in range(n) :
        distances[i] = inf

    distances[source] = 0

    for i in range(n - 1) :
        for u, v, w in edges :
            if (distances[u] != inf) and (distances[u] + w < distances[v]) :
                distances[v] = distances[u] + w

    for u, v, w in edges :
        if (distances[u] != inf) and (distances[u] + w < distances[v]) :
            return True

    return False

def has_cycle() :
    visited = [False for i in range(n)]
    distances = [inf for i in range(n)]

    for i in range(n) :
        if not visited[i] :
            if Bellman_Ford(i, distances) :
                return True
            for i in range(n) :
                if distances[i] != inf :
                    visited[i] = True

    return False


n = int(input())
m = int(input())

edges = []

for i in range(m):
    u, v, w = map(float, input().split())
    edges.append((int(u), int(v), -log(w)))

if (has_cycle()) :
    print("YES")
else:
    print("NO")
