# https://chatgpt.com/share/678b8730-6068-8003-a984-6a0c36440630
# https://chatgpt.com/share/678b6f5b-39d0-8003-b5a8-0579b100ba4f
# https://chatgpt.com/share/678bfd83-f75c-800a-ac62-cf6a5e56b6ac
from collections import deque, defaultdict

class Dinic:
    def __init__(self, n):
        self.n = n
        self.adj = [[] for _ in range(n)]
        self.capacity = defaultdict(int)

    def add_edge(self, u, v, cap):
        if cap > 0:
            self.adj[u].append(v)
            self.adj[v].append(u)
            self.capacity[(u, v)] += cap
            self.capacity[(v, u)] += 0

    def bfs(self, source, sink, level):
        for i in range(len(level)):
            level[i] = -1
        level[source] = 0
        queue = deque([source])

        while queue:
            u = queue.popleft()
            for v in self.adj[u]:
                if level[v] == -1 and self.capacity[(u, v)] > 0:
                    level[v] = level[u] + 1
                    queue.append(v)
                    if v == sink:
                        return True
        return False

    def dfs(self, u, sink, flow, level, ptr):
        if u == sink:
            return flow

        while ptr[u] < len(self.adj[u]):
            v = self.adj[u][ptr[u]]
            if level[v] == level[u] + 1 and self.capacity[(u, v)] > 0:
                pushed = self.dfs(v, sink, min(flow, self.capacity[(u, v)]), level, ptr)
                if pushed > 0:
                    self.capacity[(u, v)] -= pushed
                    self.capacity[(v, u)] += pushed
                    return pushed
            ptr[u] += 1
        return 0

    def max_flow(self, source, sink):
        total_flow = 0
        level = [-1] * self.n

        while self.bfs(source, sink, level):
            ptr = [0] * self.n
            while True:
                pushed = self.dfs(source, sink, float('inf'), level, ptr)
                if pushed == 0:
                    break
                total_flow += pushed

        return total_flow

# Main function to solve the problem
def solve():
    n = int(input())
    grid = [input().strip() for _ in range(2 * n - 1)]

    source, sink = 0, 1
    node_offset = 2

    node_map = [[0 for _ in range(n)] for _ in range(n)]
    node_count = 0

    for i in range(1, 2 * n - 2, 2):
        for j in range(1, 2 * n - 2, 2):
            node_map[(i - 1) // 2][(j - 1) // 2] = node_offset + node_count
            node_count += 1

    dinic = Dinic(node_offset + node_count)

    for i in range(n - 1):
        for j in range(n - 1):
            current_node = node_map[i][j]
            edges = 0

            if grid[2 * i][2 * j + 1] == '-':
                edges += 1
            if grid[2 * i + 2][2 * j + 1] == '-':
                edges += 1
            if grid[2 * i + 1][2 * j] == '|':
                edges += 1
            if grid[2 * i + 1][2 * j + 2] == '|':
                edges += 1

            remaining_capacity = 3 - edges

            if (i + j) % 2 == 0:
                dinic.add_edge(source, current_node, remaining_capacity)

                if i > 0 and grid[2 * i][2 * j + 1] != '-':
                    dinic.add_edge(current_node, node_map[i - 1][j], 1)
                if i == 0 and grid[2 * i][2 * j + 1] != '-':
                    dinic.add_edge(current_node, sink, 1)
                if i < n - 2 and grid[2 * i + 2][2 * j + 1] != '-':
                    dinic.add_edge(current_node, node_map[i + 1][j], 1)
                if i == n - 2 and grid[2 * i + 2][2 * j + 1] != '-':
                    dinic.add_edge(current_node, sink, 1)
                if j > 0 and grid[2 * i + 1][2 * j] != '|':
                    dinic.add_edge(current_node, node_map[i][j - 1], 1)
                if j == 0 and grid[2 * i + 1][2 * j] != '|':
                    dinic.add_edge(current_node, sink, 1)
                if j < n - 2 and grid[2 * i + 1][2 * j + 2] != '|':
                    dinic.add_edge(current_node, node_map[i][j + 1], 1)
                if j == n - 2 and grid[2 * i + 1][2 * j + 2] != '|':
                    dinic.add_edge(current_node, sink, 1)

            else:
                dinic.add_edge(current_node, sink, remaining_capacity)

                if i > 0 and grid[2 * i][2 * j + 1] != '-':
                    dinic.add_edge(node_map[i - 1][j], current_node, 1)
                if i == 0 and grid[2 * i][2 * j + 1] != '-':
                    dinic.add_edge(source, current_node, 1)
                if i < n - 2 and grid[2 * i + 2][2 * j + 1] != '-':
                    dinic.add_edge(node_map[i + 1][j], current_node, 1)
                if i == n - 2 and grid[2 * i + 2][2 * j + 1] != '-':
                    dinic.add_edge(source, current_node, 1)
                if j > 0 and grid[2 * i + 1][2 * j] != '|':
                    dinic.add_edge(node_map[i][j - 1], current_node, 1)
                if j == 0 and grid[2 * i + 1][2 * j] != '|':
                    dinic.add_edge(source, current_node, 1)
                if j < n - 2 and grid[2 * i + 1][2 * j + 2] != '|':
                    dinic.add_edge(node_map[i][j + 1], current_node, 1)
                if j == n - 2 and grid[2 * i + 1][2 * j + 2] != '|':
                    dinic.add_edge(source, current_node, 1)

    max_flow = dinic.max_flow(source, sink)
    print(max_flow)

# Example Usage
if __name__ == "__main__":
    solve()
