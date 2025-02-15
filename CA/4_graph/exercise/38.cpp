#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

unordered_map<int, int> edge_to_index;

struct Edge {
    int u, v, weight, index;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
    bool operator==(const Edge &other) const {
        return (u == other.u && v == other.v || v == other.u && u == other.v) && weight == other.weight;
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
            if (rank[root_u] < rank[root_v])
                swap(root_u, root_v);
            parent[root_v] = root_u;
            if (rank[root_u] == rank[root_v])
                rank[root_u]++;
            return true;
        }
        return false;
    }
};

void dfs(const int &node, const int &target, const vector<vector<pair<int, int>>> &adj, 
         vector<bool> &visited, int target_weight, vector<Edge> &edges) {
    visited[node] = true;
    for (const auto &[next, weight] : adj[node]) {
        if (!visited[next] && weight == target_weight) {
            edges.emplace_back(Edge{node, next, weight, -1}); // Collect the edge
            if (next == target) continue;; // Don't stop if we find the target; collect all paths
            dfs(next, target, adj, visited, target_weight, edges);
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
        edge_to_index[edges[i].u * m + edges[i].v] = i;
        edge_to_index[edges[i].v * m + edges[i].u] = i;
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    vector<Edge> mst;
    map<int, vector<Edge>> weight_groups;

    for (const auto &edge : edges) {
        if (uf.union_sets(edge.u, edge.v)) {
            mst.push_back(edge);
            weight_groups[edge.weight].push_back(edge);
        }
    }

    vector<vector<pair<int, int>>> adj(n);
    for (const auto &edge : mst) {
        adj[edge.u].emplace_back(edge.v, edge.weight);
        adj[edge.v].emplace_back(edge.u, edge.weight);
    }

    vector<string> result(m, "any"); 

    for (const auto &edge : edges) {
        if (find(mst.begin(), mst.end(), edge) != mst.end())
            continue;

        // Check if edge is part of the MSF
        vector<bool> visited(n, false);
        vector<Edge> path;
        dfs(edge.u, edge.v, adj, visited, edge.weight, path);

        if (!path.empty()) {
            result[edge.index] = "at least one";
            for (const auto &[u, v, w, i] : path) {
                result[edge_to_index[u * m + v]] = "at least one";
            }
        } else {
            result[edge.index] = "none";
        }
    }

    for (const auto &res : result)
        cout << res << endl;

    return 0;
}
