from collections import defaultdict

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            elif self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1

def find_mst_cost(n, edges, skip_edge=None, force_edges=[]):
    uf = UnionFind(n)
    mst_cost = 0
    mst_edges = 0

    # Add forced edges first
    for u, v, w in force_edges:
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            mst_cost += w
            mst_edges += 1

    # Add other edges
    for i, (u, v, w) in enumerate(edges):
        if i == skip_edge:
            continue
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            mst_cost += w
            mst_edges += 1
            if mst_edges == n - 1:
                break

    # Check if we formed a valid MST
    if mst_edges == n - 1:
        return mst_cost
    return float('inf')

# Input processing
n, m = map(int, input().split())
edges = []
for _ in range(m):
    u, v, w = map(int, input().split())
    edges.append((u - 1, v - 1, w))  # 0-based indexing

edges.sort(key=lambda x: x[2])  # Sort edges by weight

# Find the MST cost
base_mst_cost = find_mst_cost(n, edges)

# Determine critical and non-critical edges
critical = set()
non_critical = set()
for i, (u, v, w) in enumerate(edges):
    # Check if the edge is critical
    cost_without_edge = find_mst_cost(n, edges, skip_edge=i)
    if cost_without_edge > base_mst_cost:
        critical.add(i + 1)
    else:
        # Check if the edge is non-critical
        cost_with_only_this_edge = find_mst_cost(n, edges, force_edges=[(u, v, w)])
        if cost_with_only_this_edge == base_mst_cost:
            non_critical.add(i + 1)

# Process queries
q = int(input())
results = []
for _ in range(q):
    query = list(map(int, input().split()))
    k = query[0]
    bridges = query[1:]

    # Check if all requested bridges are critical
    if all(b in critical for b in bridges):
        results.append("YES")
    else:
        results.append("NO")

# Output results
print("\n".join(results))
