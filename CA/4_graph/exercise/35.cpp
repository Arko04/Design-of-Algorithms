#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

struct Edge {
    int u, v, weight, index;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
    bool operator==(const Edge &other) const {
        return (u == other.u && v == other.v || v == other.u && u == other.v ) && weight == other.weight;
    }
};

struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    bool union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v) {
            if (rank[root_u] < rank[root_v]) {
                swap(root_u, root_v);
            }
            parent[root_v] = root_u;
            if (rank[root_u] == rank[root_v]) {
                rank[root_u]++;
            }
            return true;
        }
        return false;
    }
};

// DFS to find the path from u to v in the MST and collect the weights
void dfs(int node, int target, vector<pair<int, int>> adj[], vector<bool> &visited, set<int> &weights, vector<pair<int, int>> &path) {
    if (node == target) return;  // Stop if we reach the target

    visited[node] = true;
    for (auto &[next, weight] : adj[node]) {
        if (!visited[next]) {
            weights.insert(weight);  // Add the weight to the set
            path.emplace_back(node, next);  // Add the edge to the path
            dfs(next, target, adj, visited, weights, path);  // Continue DFS
            if (!weights.empty()) return;  // If we have found the target, stop
            path.pop_back();  // Backtrack, remove the edge from the path
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--;
        edges[i].v--;
        edges[i].index = i;
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    vector<Edge> mst;

    // Step 1: Kruskal's algorithm to find MST
    for (const auto &edge : edges) {
        if (uf.union_sets(edge.u, edge.v)) {
            mst.push_back(edge);
        }
    }

    // Build adjacency list for MST
    vector<pair<int, int>> adj[n];
    for (const auto &edge : mst) {
        adj[edge.u].emplace_back(edge.v, edge.weight);
        adj[edge.v].emplace_back(edge.u, edge.weight);
    }

    vector<string> result(m, "any");

    // Step 2: Check each edge
    for (const auto &edge : edges) {
        // Skip if the edge is already in the MST
        if (find(mst.begin(), mst.end(), edge) != mst.end()) {
            continue;
        }

        if (result[edge.index] == "at least one") {
            continue;
        }

        vector<bool> visited(n, false);
        set<int> weights;
        vector<pair<int, int>> path;

        // Perform DFS to find the path and the weights used
        dfs(edge.u, edge.v, adj, visited, weights, path);

        if (weights.count(edge.weight)) {
            result[edge.index] = "at least one";
            for (const auto &[u, v] : path) {
                // Mark all edges in the path with this weight as "at least one"
                for (auto &e : mst) {
                    if (((e.u == u && e.v == v) || (e.u == v && e.v == u)) && e.weight == edge.weight) {
                        result[e.index] = "at least one";
                    }
                }
            }
        }
        else {
            result[edge.index] = "none";
        }
    }

    // Output the results
    for (const auto &res : result) {
        cout << res << endl;
    }

    return 0;
}
