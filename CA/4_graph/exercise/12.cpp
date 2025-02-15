#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
bitset <10000000000> bits;
// This is the implementation of dfs using stack and iterative loop, not recursive function
void dfs(vector<bool> &visited, const vector<vector<unsigned int> > &adjacency_list,const unsigned int &v)
{
    vector<int> node_stack;
    visited[v] = true;
    node_stack.push_back(v);
    while (!node_stack.empty())
    {
        int u = node_stack[node_stack.size()-1];
        node_stack.pop_back();
        for (int k : adjacency_list[u])
        {
            if (!visited[k])
            {
                visited[k] = true;
                node_stack.push_back(k);
            }
        }
    }
}
void dfs_on_air(vector<bool> &visited,const int &v, const int &n)
{
    vector<int> node_stack;
    visited[v] = true;
    node_stack.push_back(v);
    while (!node_stack.empty())
    {
        int u = node_stack[node_stack.size()-1];
        node_stack.pop_back();
        for (int k = 0; k < n; k++)
        {
            if (!visited[k] && bits[u*100000 + k]==0)
            {
                visited[k] = true;
                node_stack.push_back(k);
            }
        }
    }
}
int main()
{
    unsigned int n, m, u, v;
    cin >> n >> m;
    vector<bool> visited(n, false);
    vector<vector<unsigned int> > adjacency_list(n);

    for (unsigned int i = 0; i < n; i++)
    {
        bits[i * 100000 + i] = 1;
    }
    for (unsigned int i = 1; i <= m; i++)
    {
        cin >> u >> v;
        u -=1;
        v -=1;
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
        bits[u*100000 + v] = 1;
        bits[v*100000 + u] = 1;

    }

    unsigned int count = 0;
    for (unsigned int i = 0; i <= n-1; i++)
    {
        if (visited[i] == false)
        {
            count++;
            dfs(visited, adjacency_list, i);
        }
    }
    if (count != 1)
    {
        cout << 0 << endl;
        return 0;
    }

    count = 0;
    for (unsigned int i = 0; i <= n; i++)visited[i] = false; // for all
    for (unsigned int i = 0; i <= n-1; i++)
    {
        if (visited[i] == false)
        {
            count++;
            dfs_on_air(visited, i,n);
        }
    }
    cout << count - 1 <<endl;
    return 0;
}