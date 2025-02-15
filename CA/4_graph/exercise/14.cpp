#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

// This is the implementation of dfs using stack and iterative loop, not recursive function
void dfs(vector<bool> &visited, const vector<vector<unsigned int>> &adjacency_list, const unsigned int &v)
{
    vector<int> node_stack;
    visited[v] = true;
    node_stack.push_back(v);
    while (!node_stack.empty())
    {
        unsigned int u = node_stack[node_stack.size() - 1];
        node_stack.pop_back();
        for (unsigned k : adjacency_list[u])
        {
            if (!visited[k])
            {
                visited[k] = true;
                node_stack.push_back(k);
            }
        }
    }
}
 
int main()
{
    unsigned int n, m;
    vector<unsigned int> u(m), v(m);
    cin >> n >> m;
    vector<bool> visited(n + 1, false);
    vector<vector<unsigned int>> adjacency_list(n + 1);
    for (unsigned int i = 0; i < m; i++)
    {
        cin >> u[i] >> v[i];
        u[i] -= 1;
        v[i] -= 1;
        adjacency_list[u[i]].push_back(v[i]);
        adjacency_list[v[i]].push_back(u[i]);
    }

    unsigned int count = 0;
    for (unsigned int i = 0; i <= n - 1; i++)
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
    else
    {
        bitset<10000000000> bits;
        for (unsigned int i = 0; i < n; i++)
        {
            bits[i * 100000 + i] = 1;
        }

        for (unsigned int i = 0; i < m; i++)
        {
            bits[u[i] * 100000 + v[i]] = 1;
            bits[v[i] * 100000 + u[i]] = 1;
        }
        count = 0;
        for (unsigned int i = 0; i < n; i++)
        {
            visited[i] = false;
        }

        for (unsigned int i = 0; i <= n - 1; i++)
        {
            if (visited[i] == false)
            {
                count++;
                vector<int> node_stack;
                visited[i] = true;
                node_stack.push_back(i);
                while (!node_stack.empty())
                {
                    unsigned int u = node_stack[node_stack.size() - 1];
                    node_stack.pop_back();
                    for (unsigned int k = 0; k < n; k++)
                    {
                        if (!visited[k] && bits[u * 100000 + k] == 0)
                        {
                            visited[k] = true;
                            node_stack.push_back(k);
                        }
                    }
                }
            }
        }

        cout << count - 1 << endl;
        return 0;
    }
}