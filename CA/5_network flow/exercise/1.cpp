// https://chatgpt.com/share/678b8730-6068-8003-a984-6a0c36440630
// https://chatgpt.com/share/678b6f5b-39d0-8003-b5a8-0579b100ba4f
// https://chatgpt.com/share/678bfd83-f75c-800a-ac62-cf6a5e56b6ac
// https://chatgpt.com/share/678bfd83-f75c-800a-ac62-cf6a5e56b6ac
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 1000000000; // A large value to represent infinity
const int k = 2000;         // Maximum number of nodes
int c[k][k];                // Capacity matrix
int f[k][k];                // Flow matrix
int level[k];               // Level graph
int ptr[k];                 // Pointer for current edge in DFS

// BFS to construct level graph
bool bfs(int source, int sink, int n) {
    fill(level, level + n, -1);
    queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (level[v] == -1 && c[u][v] - f[u][v] > 0) { // Residual capacity > 0
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[sink] != -1; // Return true if sink is reachable
}

// DFS to send flow along augmenting paths
int dfs(int u, int sink, int flow, int n) {
    if (u == sink) return flow;

    for (int &i = ptr[u]; i < n; ++i) {
        int v = i;
        if (level[v] == level[u] + 1 && c[u][v] - f[u][v] > 0) {
            int pushed = dfs(v, sink, min(flow, c[u][v] - f[u][v]), n);
            if (pushed > 0) {
                f[u][v] += pushed;
                f[v][u] -= pushed;
                return pushed;
            }
        }
    }
    return 0;
}

// Dinic's algorithm for maximum flow
int dinic(int source, int sink, int n) {
    memset(f, 0, sizeof(f));
    int max_flow = 0;

    while (bfs(source, sink, n)) {
        memset(ptr, 0, sizeof(ptr));
        while (int pushed = dfs(source, sink, INF, n)) {
            max_flow += pushed;
        }
    }
    return max_flow;
}

// Function to add edges to the graph
void add_edge(int u, int v, int capacity) {
    c[u][v] += capacity;
}

// Main function
int main() {
    int n;
    cin >> n;

    memset(c, 0, sizeof(c));
    vector<string> grid(2 * n - 1);
    for (int i = 0; i < 2 * n - 1; ++i) {
        cin >> grid[i];
    }

    int source = 0, sink = 1;
    int node_offset = 2; // Nodes start after source and sink
    vector<vector<int>> node_map(n, vector<int>(n, 0));
    int node_count = 0;

    // Map grid centers to graph nodes
    for (int i = 1; i < 2 * n - 2; i += 2) {
        for (int j = 1; j < 2 * n - 2; j += 2) {
            node_map[(i - 1) / 2][(j - 1) / 2] = node_offset + node_count++;
        }
    }

    // Add edges based on the grid
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            int current_node = node_map[i][j];
            int edges = 0;

            // Count the edges around the center
            if (grid[2 * i][2 * j + 1] == '-') edges++; // Top edge
            if (grid[2 * i + 2][2 * j + 1] == '-') edges++; // Bottom edge
            if (grid[2 * i + 1][2 * j] == '|') edges++; // Left edge
            if (grid[2 * i + 1][2 * j + 2] == '|') edges++; // Right edge

            int remaining_capacity = 3 - edges;

            if ((i + j) % 2 == 0) {
                add_edge(source, current_node, remaining_capacity);

                if (i > 0 && grid[2 * i][2 * j + 1] != '-') add_edge(current_node, node_map[i - 1][j], 1); // Up
                if (i < n - 2 && grid[2 * i + 2][2 * j + 1] != '-') add_edge(current_node, node_map[i + 1][j], 1); // Down
                if (j > 0 && grid[2 * i + 1][2 * j] != '|') add_edge(current_node, node_map[i][j - 1], 1); // Left
                if (j < n - 2 && grid[2 * i + 1][2 * j + 2] != '|') add_edge(current_node, node_map[i][j + 1], 1); // Right
            } else {
                add_edge(current_node, sink, remaining_capacity);

                if (i > 0 && grid[2 * i][2 * j + 1] != '-') add_edge(node_map[i - 1][j], current_node, 1); // Up
                if (i < n - 2 && grid[2 * i + 2][2 * j + 1] != '-') add_edge(node_map[i + 1][j], current_node, 1); // Down
                if (j > 0 && grid[2 * i + 1][2 * j] != '|') add_edge(node_map[i][j - 1], current_node, 1); // Left
                if (j < n - 2 && grid[2 * i + 1][2 * j + 2] != '|') add_edge(node_map[i][j + 1], current_node, 1); // Right
            }
        }
    }

    int max_flow = dinic(source, sink, node_offset + node_count);
    cout << max_flow << endl;

    return 0;
}
