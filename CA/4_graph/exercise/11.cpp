#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;
void dfs(vector<bool> &visited, vector<vector<ll>> &adjacency_list, ll &v)
{
    visited[v] = true;
    for (ll u : adjacency_list[v])
    {
        if (visited[u] == false)
        {
            dfs(visited, adjacency_list, u);
        }
    }
}
int main()
{
    ll n, m, u, v;
    cin >> n >> m;
    vector<bool> visited(n+1, false);
    vector<vector<ll>> adjacency_list(n+1);
    for (ll i = 1; i <= m; i++)
    {
        cin >> u >> v;
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    ll count = 0;
    for (ll i = 1; i <= n; i++)
    {
        if (visited[i] == false)
        {
            count++;
            dfs(visited, adjacency_list, i);
        }
    }
    if (count == 1)
    {
        cout << n - 1 << endl;
    }
    else
    {
        cout << 0 << endl;
    }
    return 0;
}