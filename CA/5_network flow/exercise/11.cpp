#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Define the maximum number of nodes
const int MAXN = 6400; // Large enough for n <= 80
const int INF = INT_MAX;

// Structure to represent an edge
struct Edge {
    int to, rev, cap;
};

// Graph representation
vector<Edge> graph[MAXN];
int level[MAXN], ptr[MAXN];
int source, sink;

// Add an edge to the graph
void add_edge(int u, int v, int cap) {
    graph[u].push_back({v, (int)graph[v].size(), cap});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0}); // Reverse edge with 0 capacity
}

// Perform BFS to build level graph
bool bfs() {
    fill(level, level + MAXN, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& edge : graph[u]) {
            if (edge.cap > 0 && level[edge.to] == -1) {
                level[edge.to] = level[u] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[sink] != -1;
}

// Perform DFS to find augmenting paths
int dfs(int u, int flow) {
    if (u == sink) return flow;
    for (int& i = ptr[u]; i < (int)graph[u].size(); i++) {
        Edge& edge = graph[u][i];
        if (edge.cap > 0 && level[edge.to] == level[u] + 1) {
            int pushed = dfs(edge.to, min(flow, edge.cap));
            if (pushed > 0) {
                edge.cap -= pushed;
                graph[edge.to][edge.rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

// Dinic's algorithm
int dinic() {
    int max_flow = 0;
    while (bfs()) {
        fill(ptr, ptr + MAXN, 0);
        while (int flow = dfs(source, INF)) {
            max_flow += flow;
        }
    }
    return max_flow;
}

int main() {
    int n;
    cin >> n;

    vector<string> grid(2 * n - 1);
    for (int i = 0; i < 2 * n - 1; i++) {
        cin >> grid[i];
    }

    // Source and sink
    source = 0;
    sink = 1;
    int node_offset = 2; // Nodes start after source and sink

    // Map grid centers to graph nodes
    vector<vector<int>> node_map(n - 1, vector<int>(n - 1, 0));
    int node_count = 0;

    for (int i = 1; i < 2 * n - 2; i += 2) {
        for (int j = 1; j < 2 * n - 2; j += 2) {
            node_map[(i - 1) / 2][(j - 1) / 2] = node_offset + node_count++;
        }
    }

    // Add edges based on the grid
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            int current_node = node_map[i][j];
            int edges = 0;

            // Count the number of edges around the center
            if (grid[2 * i][2 * j + 1] == '-') edges++; // Top edge
            if (grid[2 * i + 2][2 * j + 1] == '-') edges++; // Bottom edge
            if (grid[2 * i + 1][2 * j] == '|') edges++; // Left edge
            if (grid[2 * i + 1][2 * j + 2] == '|') edges++; // Right edge

            // Add capacity based on remaining edge possibilities
            int remaining_capacity = 3 - edges;

            if ((i + j) % 2 == 0) {
                // Left partition
                add_edge(source, current_node, remaining_capacity);
            } else {
                // Right partition
                add_edge(current_node, sink, remaining_capacity);
            }

            // Connect to adjacent nodes
            if (i > 0) add_edge(current_node, node_map[i - 1][j], 1); // Up
            if (i < n - 2) add_edge(current_node, node_map[i + 1][j], 1); // Down
            if (j > 0) add_edge(current_node, node_map[i][j - 1], 1); // Left
            if (j < n - 2) add_edge(current_node, node_map[i][j + 1], 1); // Right
        }
    }

    // Calculate maximum flow
    int max_flow = dinic();
    cout << max_flow << endl;

    return 0;
}
