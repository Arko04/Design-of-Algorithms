// https://chatgpt.com/share/676ae353-43c4-8003-9d83-a55c7b832eb3
// https://chatgpt.com/share/676ad7c0-18d4-8003-baa8-ed6059fe2cf0
// https://chatgpt.com/share/676ad9a3-ca70-8003-9312-f2d5dcb78cd4
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

struct Edge
{
    int u, v, weight, index;
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
    bool operator==(const Edge &other) const
    {
        return u == other.u && v == other.v && weight == other.weight && index == other.index;
    }
};

struct UnionFind
{
    vector<int> parent, rank;

    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u)
    {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    bool union_sets(int u, int v)
    {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v)
        {
            if (rank[root_u] < rank[root_v])
            {
                swap(root_u, root_v);
            }
            parent[root_v] = root_u;
            if (rank[root_u] == rank[root_v])
            {
                rank[root_u]++;
            }
            return true;
        }
        return false;
    }
};

void dfs(int node, int target, vector<pair<int, int>> adj[], vector<bool> &visited, set<int> &weights, vector<Edge> &path)
{
    if (node == target)
        return;

    visited[node] = true;
    for (auto &[next, weight] : adj[node])
    {
        if (!visited[next])
        {
            weights.insert(weight);
            path.emplace_back(node, next,  weight, index?????????);
            dfs(next, target, adj, visited, weights, path);
            if (!weights.empty())
                return;
            path.pop_back();
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--;
        edges[i].v--;
        edges[i].index = i;
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    vector<Edge> mst;
    map<int, vector<Edge>> weight_groups;

    // Step 1: Kruskal's algorithm to find MST
    for (const auto &edge : edges)
    {
        if (uf.union_sets(edge.u, edge.v))
        {
            mst.push_back(edge);
            weight_groups[edge.weight].push_back(edge);
        }
    }

    vector<pair<int, int>> adj[n];
    for (const auto &edge : mst)
    {
        adj[edge.u].emplace_back(edge.v, edge.weight);
        adj[edge.v].emplace_back(edge.u, edge.weight);
    }

    vector<string> result(m, "any");

    // Step 2: Check each edge
    for (const auto &edge : edges)
    {
        // if you find the edge in the mst
        if (find(mst.begin(), mst.end(), edge) != mst.end())
        {
            continue;
        }
        if (result[edge.index] == "at least one")
        {
            continue;
        }

        vector<bool> visited(n, false);
        set<int> weights;
        vector<Edge> path;
        dfs(edge.u, edge.v, adj, visited, weights, path);

        if (weights.count(edge.weight))
        {
            result[edge.index] = "at least one";
            for (const auto e : path)
            {
                // Mark all edges in the path with this weight as "at least one"
                if (e.weight == edge.weight)
                {
                    result[e.index] = "at least one";
                }
            }
        }
        else
        {
            result[edge.index] = "none";
        }
    }

    for (const auto &res : result)
    {
        cout << res << endl;
    }

    return 0;
}
