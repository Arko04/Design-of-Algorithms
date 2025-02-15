#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;
#define INF 1000000000
const int k = 1000;
int f[k][k];
int c[k][k];

void dfs_ford_fulkeron(vector<set<int>> &outgoing, vector<set<int>> &incoming, vector<int> &flow, vector<int> &parent, int u, int x)
{
    flow[u] = x;
    for (int v : outgoing[u])
    {
        if (flow[v] == -1 && c[u][v] - f[u][v] > 0)
        {
            parent[v] = u;
            dfs_ford_fulkeron(outgoing, incoming, flow, parent, v, min(x, c[u][v] - f[u][v]));
        }
    }
    for (int v : incoming[u])
    {
        if (flow[v] == -1 && f[v][u] > 0)
        {
            parent[v] = u;
            dfs_ford_fulkeron(outgoing, incoming, flow, parent, v, min(x, f[v][u]));
        }
    }
}

vector<int> dfs(const vector<set<int>> &adj_list, vector<bool> &visited, const int &v, const int &sink)
{
    visited[v] = true;
    if (v == sink)
    {
        return vector<int>{v};
    }
    for (int u : adj_list[v])
    {
        if (visited[u] == false)
        {
            vector<int> nodes = dfs(adj_list, visited, u, sink);
            if (nodes.empty())
            {
                continue;
            }
            else
            {
                nodes.push_back(v);
                return nodes;
            }
        }
    }
    return vector<int>{};
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<set<int>> outgoing(n);
    vector<set<int>> incoming(n);
    vector<set<int>> network_flow_graph(n);
    vector<int> flow(n), parent(n);

    memset(f, 0, sizeof(f));
    memset(c, 0, sizeof(c));

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        outgoing[u].insert(v);
        incoming[v].insert(u);
        c[u][v] = 1;
    }

    int source = 0, sink = n - 1;
    while (true)
    {
        for (int i = 0; i < n; i++)
        {
            flow[i] = -1;
        }
        dfs_ford_fulkeron(outgoing, incoming, flow, parent, source, INF);

        if (flow[sink] == -1)
        {
            break;
        }

        int v = sink, x = flow[sink];
        while (v != source)
        {
            int u = parent[v];
            f[u][v] += x;
            f[v][u] -= x;
            v = u;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (f[i][j] == 1)
            {
                network_flow_graph[i].insert(j);
            }
        }
    }

    int path_no = 0;
    vector<int> nodes;
    vector<vector<int>> path_nodes;
    do
    {
        vector<bool> visited(n, false);
        nodes = dfs(network_flow_graph, visited, source, sink);
        if (nodes.empty() == true)
        {
            break;
        }
        else
        {
            path_no++;
            path_nodes.push_back(nodes);

            for (int i = 0; i < nodes.size() - 1; i++)
            {
                network_flow_graph[nodes[i + 1]].erase(nodes[i]);
            }
        }
    } while (nodes.empty() == false);
    cout << path_no << endl;
    for (int i = 0; i < path_nodes.size(); i++)
    {
        cout << path_nodes[i].size() << endl;
        for (int j = path_nodes[i].size() - 1; j >= 0; j--)
        {
            cout << path_nodes[i][j] + 1 << ' ';
        }
        cout << endl;
    }
    return 0;
}
