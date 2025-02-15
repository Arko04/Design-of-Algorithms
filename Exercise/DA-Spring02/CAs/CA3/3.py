from math import inf
from heapq import heappush, heappop
from copy import deepcopy

def Dijkstra(source, n, adj_ls) :
    distances = [inf for _ in range(n + 1)]
    visited = [False for _ in range(n + 1)]
    parents = [[] for _ in range(n + 1)]
    min_queue = []
    parents[source] = [-1]

    distances[source] = 0
    heappush(min_queue, (distances[source], source))

    while min_queue :
        d, poped_v = heappop(min_queue)
        if not visited[poped_v] :
            visited[poped_v] = True
            for u, w in adj_ls[poped_v] :
                if d != inf and d + w < distances[u] :
                    parents[u].clear()
                    parents[u].append(poped_v)
                    distances[u] = d + w
                    heappush(min_queue, (distances[u], u))
                elif d != inf and d + w == distances[u] :
                    parents[u].append(poped_v)

    return distances, parents

def find_paths(destination, source) :
    q = []
    paths = []
    path = []
    path.append(destination)
    cpath = deepcopy(path)
    q.append(cpath)

    while q :
        poped_path = q.pop(0)
        if poped_path[-1] == source :
            paths.append(poped_path)
        else :
            for each in p[poped_path[-1]] :
                if each not in poped_path :
                    new_path = deepcopy(poped_path)
                    new_path.append(each)
                    q.append(new_path)

    return paths


n, e = map(int, input().split())
m, s, t = map(int, input().split())

adj_ls = {}

for i in range(1, n + 1) :
    adj_ls[i] = []

for i in range(e) :
    a, b, w = map(int, input().split())
    adj_ls[a].append((b, w))
    adj_ls[b].append((a, w))

d, p = Dijkstra(s, n, adj_ls)
paths = find_paths(t, s)

if len(paths) == 0 :
    print(-1)
    exit()
elif len(paths) > 1 :
    common_vetices = set(paths[0]).intersection(*paths[1:])
else :
    common_vetices = paths[0]

dm, pm = Dijkstra(m, n, adj_ls)

dmin = min(dm[v] for v in common_vetices)

if dmin == inf :
    print(-1)
else :
    print(dmin)
