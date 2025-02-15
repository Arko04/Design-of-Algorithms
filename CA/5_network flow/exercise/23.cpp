#include <iostream>
#include <vector>
#include <set>

using namespace std;
#define INF 1000000000
const int k = 507;
int f[k][k];
int c[k][k];
void dfs(vector<set<int>> &outgoing, vector<set<int>> &incoming, vector<int> &flow, vector<int> &parent, int u, int x)
{
    flow[u] = x;
    for (int v : outgoing[u])
    {
        if (flow[v] == -1 && c[u][v] - f[u][v] > 0)
        {
            parent[v] = u;
            dfs(outgoing, incoming, flow, parent, v, min(x, c[u][v] - f[u][v]));
        }
    }
    for (int v : incoming[u])
    {
        if (flow[v] > 0 && f[u][v] > 0)
        {
            parent [v] = u;
            dfs(outgoing, incoming, flow, parent, v, min(x, f[u][v]));
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<set<int>> outgoing(n);
    vector<set<int>> incoming(n);
    vector<int> flow(n);

    vector<int> parent(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        outgoing[u].insert(v);
        incoming[v].insert(u);
        f[u][v] = 0;
        c[u][v] = 1;
    }
    int source = 0;
    int sink = n - 1;
    while (true)
    {
        for (int i = 0; i < n; i++)
        {
            flow[i] = -1;
        }
        dfs(outgoing, incoming, flow, parent, source, INF);

        if (flow[sink] == -1)
        {
            break;
        }
        int v = sink;
        int x = flow[sink];
        while (v != source)
        {
            int u = parent[v];
            f[u][v] += x;
            v = u;
        }
    }

    return 0;
}