#include <iostream>
#include <vector>
#include <set>

using namespace std;
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
    vector<set<int>> adj_list(n);
    
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        // adj_list[v].insert(u);
        adj_list[u].insert(v);
    }
    int path_no = 0;
    int source = 0;
    int sink = n - 1;
    vector<int> nodes;
    vector<vector<int>> path_nodes;
    // vector<bool> visited(n, false);
    do
    {
        vector<bool> visited(n, false);
        nodes = dfs(adj_list, visited, source, sink);
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
                // adj_list[nodes[i]].erase(nodes[i + 1]);
                adj_list[nodes[i + 1]].erase(nodes[i]);
            }
        }
    } while (nodes.empty() == false);
    cout << path_no << endl;
    for (int i = 0; i < path_nodes.size(); i++)
    {
        cout << path_nodes[i].size() << endl;
        for (int j = path_nodes[i].size() - 1; j >= 0; j--)
        {
            cout << path_nodes[i][j]+1 << ' ';
        }
        cout << endl;
    }
    return 0;
}