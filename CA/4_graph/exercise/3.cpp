// https://chatgpt.com/share/676da1dc-bc78-8003-abc0-ce2ed0df88b3
// https://chatgpt.com/share/676d5c40-a018-8003-a43c-3cedb1c2e862
// https://chatgpt.com/share/676ae353-43c4-8003-9d83-a55c7b832eb3
// https://chatgpt.com/share/676ad7c0-18d4-8003-baa8-ed6059fe2cf0
// https://chatgpt.com/share/676ad9a3-ca70-8003-9312-f2d5dcb78cd4
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Edge {
    int u, v, weight, idx; // Add idx if used for identification

bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
    // Equality operator for Edge
    bool operator==(const Edge &other) const {
        return u == other.u && v == other.v && weight == other.weight && idx == other.idx;
    }
};

// Specialize std::hash for Edge
namespace std {
    template <>
    struct hash<Edge> {
        size_t operator()(const Edge &e) const {
            return ((hash<int>()(e.u) ^ (hash<int>()(e.v) << 1)) >> 1) ^ 
                   (hash<int>()(e.weight) << 1) ^ hash<int>()(e.idx);
        }
    };
}

class UnionFind
{
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    bool union_sets(int u, int v)
    {
        int root_u = find(u);
        int root_v = find(v);

        // amortized
        parent[u] = root_u;
        parent[v] = root_v;

        if (root_u != root_v)
        {
            if (rank[root_u] < rank[root_v])
            {
                swap(root_u, root_v);
            }
            parent[root_v] = root_u;
            rank[root_u] += (rank[root_u] == rank[root_v]);
            return true;
        }
        return false;
    }
};

class GraphProcessor
{
private:
    int n, log_n;
    vector<vector<pair<int, int>>> msf_adj;
    vector<int> depth;
    vector<vector<int>> up;
    unordered_map<int64_t, Edge> map_edge;

    void dfs(int v, int p, int d)
    {
        depth[v] = d;
        up[v][0] = p;

        for (int i = 1; i <= log_n; i++)
        {
            if (up[v][i - 1] != -1)
            {
                up[v][i] = up[up[v][i - 1]][i - 1];
            }
        }

        for (const auto &[u, w] : msf_adj[v])
        {
            if (u != p)
            {
                dfs(u, v, d + 1);
            }
        }
    }

    int compute_lca(int u, int v)
    {
        if (depth[u] < depth[v])
        {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];
        for (int i = log_n; i >= 0; i--)
        {
            if (diff & (1 << i))
            {
                u = up[u][i];
            }
        }

        if (u == v)
            return u;

        for (int i = log_n; i >= 0; i--)
        {
            if (up[u][i] != up[v][i])
            {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

    vector<int> find_path(int u, int v)
    {
        vector<int> path;
        int lca = compute_lca(u, v);

        while (u != lca)
        {
            path.push_back(u);
            u = up[u][0];
        }
        path.push_back(lca);

        vector<int> path_v;
        while (v != lca)
        {
            path_v.push_back(v);
            v = up[v][0];
        }

        path.insert(path.end(), path_v.rbegin(), path_v.rend());
        return path;
    }

public:
    GraphProcessor(int vertices) : n(vertices)
    {
        log_n = 32 - __builtin_clz(n); // Calculate log2(n)
        msf_adj.resize(n);
        depth.resize(n);
        up.assign(n, vector<int>(log_n + 1, -1));
    }

    void add_edge(const Edge &edge)
    {
        map_edge[edge.u * n + edge.v] = edge;
        map_edge[edge.v * n + edge.u] = edge;
    }

    void build_msf(vector<Edge> &edges, vector<Edge> &msf)
    {
        UnionFind uf(n);
        sort(edges.begin(), edges.end());

        for (const auto &edge : edges)
        {
            if (msf.size() == n - 1)
            {
                break;
            }
            if (uf.union_sets(edge.u, edge.v))
            {
                msf.push_back(edge);
                msf_adj[edge.u].emplace_back(edge.v, edge.weight);
                msf_adj[edge.v].emplace_back(edge.u, edge.weight);
            }
        }
    }

    void process_msf()
    {
        for (int i = 0; i < n; i++)
        {
            if (up[i][0] == -1)
            {
                dfs(i, -1, 0);
            }
        }
    }

    vector<string> process_results(const vector<Edge> &edges, const vector<Edge> &msf)
    {
        
        vector<string> result(edges.size(), "any");

        // Create a set for fast lookup
        unordered_set<Edge> msf_set(msf.begin(), msf.end());
        for (const auto &edge : edges)
        {
            if (msf_set.count(edge) > 0 || result[edge.idx] != "any")
                continue;
                
            vector<int> path = find_path(edge.u, edge.v);
            bool flag = false;

            for (size_t i = 0; i < path.size() - 1; i++)
            {
                auto it = map_edge.find(path[i] * n + path[i + 1]);

                if (it != map_edge.end() && it->second.weight == edge.weight)
                {
                    result[it->second.idx] = "at least one";
                    flag = true;
                }
            }

            result[edge.idx] = (flag) ? "at least one" : "none";
        }

        return result;
    }
};
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    GraphProcessor processor(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        edges[i] = {u, v, w, i};
        processor.add_edge(edges[i]);
    }

    vector<Edge> msf;
    processor.build_msf(edges, msf);
    processor.process_msf();

    vector<string> result = processor.process_results(edges, msf);

    for (const string &res : result)
    {
        cout << res << endl;
    }

    return 0;
}