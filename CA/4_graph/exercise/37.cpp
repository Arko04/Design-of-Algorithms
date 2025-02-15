// Find all path in preprocess
// https://chatgpt.com/share/676b98bb-82f4-8003-8489-cd4066ddab3c
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

vector<vector<int>> parent;
vector<vector<Edge>> edge_to_parent;
vector<int> depth;

void preprocess_lca(int node, int par, vector<pair<int, int>> adj[], vector<Edge> &edges) {
    for (auto &[next, weight] : adj[node]) {
        if (next != par) {
            depth[next] = depth[node] + 1;
            parent[next][0] = node;
            edge_to_parent[next][0] = {node, next, weight, edge_to_index[node * adj->size() + next]};
            preprocess_lca(next, node, adj, edges);
        }
    }
}

void build_lca(int n, vector<pair<int, int>> adj[], vector<Edge> &edges) {
    int log = 1;
    while ((1 << log) <= n) log++;
    parent.assign(n, vector<int>(log, -1));
    edge_to_parent.assign(n, vector<Edge>(log, {0, 0, 0, -1}));
    depth.assign(n, 0);

    preprocess_lca(0, -1, adj, edges);

    for (int j = 1; (1 << j) < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
                edge_to_parent[i][j] = {edge_to_parent[i][j - 1].u, edge_to_parent[parent[i][j - 1]][j - 1].v, max(edge_to_parent[i][j - 1].weight, edge_to_parent[parent[i][j - 1]][j - 1].weight), -1};
            }
        }
    }
}

vector<Edge> query_path(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int log = 1;
    while ((1 << log) <= depth[u]) log++;

    vector<Edge> path;

    for (int i = log; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            path.push_back(edge_to_parent[u][i]);
            u = parent[u][i];
        }
    }

    if (u == v) return path;

    for (int i = log; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            path.push_back(edge_to_parent[u][i]);
            path.push_back(edge_to_parent[v][i]);
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    path.push_back(edge_to_parent[u][0]);
    path.push_back(edge_to_parent[v][0]);
    return path;
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

    for (const auto &edge : edges) {
        if (uf.union_sets(edge.u, edge.v)) {
            mst.push_back(edge);
        }
    }

    vector<pair<int, int>> adj[n];
    for (const auto &edge : mst) {
        adj[edge.u].emplace_back(edge.v, edge.weight);
        adj[edge.v].emplace_back(edge.u, edge.weight);
    }

    build_lca(n, adj, edges);

    vector<string> result(m, "any");

    for (const auto &edge : edges) {
        if (find(mst.begin(), mst.end(), edge) != mst.end())
            continue;
        if (result[edge.index] == "at least one")
            continue;

        vector<Edge> path = query_path(edge.u, edge.v);
        bool found = false;
        for (const auto &e : path) {
            if (e.weight == edge.weight) {
                result[edge_to_index[e.v * m + e.u]] = "at least one";
                found = true;
            }
        }

        if (found) {
            result[edge.index] = "at least one";
        } else {
            result[edge.index] = "none";
        }
    }

    for (const auto &res : result)
        cout << res << endl;

    return 0;
}
