// https://chatgpt.com/share/678b8730-6068-8003-a984-6a0c36440630
// https://chatgpt.com/share/678b6f5b-39d0-8003-b5a8-0579b100ba4f
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 1000000000; // A large value to represent infinity
const int k = 163;         // Maximum number of nodes
int f[k][k];                // Flow matrix
int c[k][k];                // Capacity matrix

vector<int> level;

// Breadth-First Search to build level graph
bool bfs_dinic(vector<set<int>> &outgoing, int source, int sink) {
    level.assign(level.size(), -1);
    queue<int> q;
    level[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : outgoing[u]) {
            if (level[v] == -1 && c[u][v] - f[u][v] > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }

    return level[sink] != -1;
}

// Depth-First Search to send flow along augmenting paths
int dfs_dinic(vector<set<int>> &outgoing, int u, int sink, int flow) {
    if (u == sink) {
        return flow;
    }

    for (int v : outgoing[u]) {
        if (level[v] == level[u] + 1 && c[u][v] - f[u][v] > 0) {
            int min_flow = min(flow, c[u][v] - f[u][v]);
            int path_flow = dfs_dinic(outgoing, v, sink, min_flow);

            if (path_flow > 0) {
                f[u][v] += path_flow;
                f[v][u] -= path_flow;
                return path_flow;
            }
        }
    }

    return 0;
}

// Dinic's algorithm for Maximum Flow
int dinic(vector<set<int>> &outgoing, int n, int source, int sink) {
    memset(f, 0, sizeof(f)); // Initialize flow matrix
    level.resize(n);

    int max_flow = 0;

    while (bfs_dinic(outgoing, source, sink)) {
        while (int flow = dfs_dinic(outgoing, source, sink, INF)) {
            max_flow += flow;
        }
    }

    return max_flow;
}

// Function to add edges to the graph
void add_edge(vector<set<int>> &outgoing, vector<set<int>> &incoming, int u, int v, int capacity) {
    if (capacity == 0) {
        return;
    }
    if (c[u][v] == 0) {
        outgoing[u].insert(v);
        incoming[v].insert(u);
        c[u][v] = capacity;
    } else {
        if (u == 0 || v == 1) {
            c[u][v] += capacity;
        }
    }
    // cout << "edge from: " << u << " to " << v << " with cap " << c[u][v] << " is added" << endl;
}

int main() {
    int n;
    cin >> n;

    memset(c, 0, sizeof(c)); // Initialize all elements to 0
    vector<string> grid(2 * n - 1);
    for (int i = 0; i < 2 * n - 1; i++) {
        cin >> grid[i];
    }

    vector<set<int>> outgoing(k), incoming(k); // Adjacency lists

    // Source and sink
    int source = 0, sink = 1;
    int node_offset = 2; // Nodes start after source and sink

    // Map grid centers to graph nodes
    vector<vector<int>> node_map(n, vector<int>(n, 0));
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

            if (grid[2 * i][2 * j + 1] == '-')
                edges++; // Top edge
            if (grid[2 * i + 2][2 * j + 1] == '-')
                edges++; // Bottom edge
            if (grid[2 * i + 1][2 * j] == '|')
                edges++; // Left edge
            if (grid[2 * i + 1][2 * j + 2] == '|')
                edges++; // Right edge

            int remaining_capacity = 3 - edges; // Remaining edges that can be drawn

            if ((i + j) % 2 == 0) {
                add_edge(outgoing, incoming, source, current_node, remaining_capacity);

                if (i > 0 && grid[2 * i][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, current_node, node_map[i - 1][j], 1); // Up
                if (i == 0 && grid[2 * i][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, current_node, sink, 1);
                if (i < n - 2 && grid[2 * i + 2][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, current_node, node_map[i + 1][j], 1); // Down
                if (i == n - 2 && grid[2 * i + 2][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, current_node, sink, 1);
                if (j > 0 && grid[2 * i + 1][2 * j] != '|')
                    add_edge(outgoing, incoming, current_node, node_map[i][j - 1], 1); // Left
                if (j == 0 && grid[2 * i + 1][2 * j] != '|')
                    add_edge(outgoing, incoming, current_node, sink, 1);
                if (j < n - 2 && grid[2 * i + 1][2 * j + 2] != '|')
                    add_edge(outgoing, incoming, current_node, node_map[i][j + 1], 1); // Right
                if (j == n - 2 && grid[2 * i + 1][2 * j + 2] != '|')
                    add_edge(outgoing, incoming, current_node, sink, 1);
            } else {
                add_edge(outgoing, incoming, current_node, sink, remaining_capacity);

                if (i > 0 && grid[2 * i][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, node_map[i - 1][j], current_node, 1); // Up
                if (i == 0 && grid[2 * i][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, source, current_node, 1);
                if (i < n - 2 && grid[2 * i + 2][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, node_map[i + 1][j], current_node, 1); // Down
                if (i == n - 2 && grid[2 * i + 2][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, source, current_node, 1);
                if (j > 0 && grid[2 * i + 1][2 * j] != '|')
                    add_edge(outgoing, incoming, node_map[i][j - 1], current_node, 1); // Left
                if (j == 0 && grid[2 * i + 1][2 * j] != '|')
                    add_edge(outgoing, incoming, source, current_node, 1);
                if (j < n - 2 && grid[2 * i + 1][2 * j + 2] != '|')
                    add_edge(outgoing, incoming, node_map[i][j + 1], current_node, 1); // Right
                if (j == n - 2 && grid[2 * i + 1][2 * j + 2] != '|')
                    add_edge(outgoing, incoming, source, current_node, 1);
            }
        }
    }

    // Calculate maximum flow
    int max_flow = dinic(outgoing, node_offset + node_count, source, sink);
    cout << max_flow << endl;

    return 0;
}
