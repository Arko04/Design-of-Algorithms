// https://chatgpt.com/share/6745cc55-8ce4-8009-a4b0-84dbec2ba7b6
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

set<int> DFS_to_find_leaf_set(vector<set<int>> &leafs_of_each_node, vector<vector<int>> &adj_list, vector<bool> &visited, int v)
{
    visited[v] = true;
    set<int> leafs_index;

    bool isLeaf = true; // Assume the node is a leaf
    for (int u : adj_list[v])
    { // Iterate over the neighbors of v
        if (!visited[u])
        {
            isLeaf = false; 
            set<int> leafs_index_of_u = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, u);
            leafs_index.insert(leafs_index_of_u.begin(), leafs_index_of_u.end()); // Merge sets
        }
    }

    if (isLeaf)
    {
        leafs_index.insert(v);
    }

    leafs_of_each_node[v] = leafs_index; 
    return leafs_index;
}

pair<int, int> DFS(vector<vector<int>> &adj_list, const vector<int> &heights, vector<int> &e, vector<bool> &visited, int v)
{
    visited[v] = true;
    pair<int, int> max_leaf = {0, 0};
    bool is_leaf = true;

    for (int u = 0; u < adj_list[v].size(); u++)
    {
        if (!visited[u])
        {
            is_leaf = false;
            pair<int, int> leaf = DFS(adj_list, heights, e, visited, adj_list[v][u]);
            if (leaf.second > max_leaf.second) // value
            {
                max_leaf.first = leaf.first;
                max_leaf.second = leaf.second;
            }
        }
    }
    if (is_leaf)
    {
        e[v] = heights[v];
        return pair<int, int>{v, e[v]};
    }
    if (max_leaf.second >= heights[v])
    {
        return max_leaf;
    }
    else
    {
        e[max_leaf.first] = heights[v];
        return (pair<int, int>){max_leaf.first, heights[v]};
    }
}
int calc_for_root(vector<set<int>> &leafs_of_each_node, vector<vector<int>> &adj_list, const vector<int> &heights, vector<int> &e, vector<bool> &visited, int v)
{
    visited[v] = true;
    pair<int, int> max_leaf = {0, 0};
    bool is_leaf = true;
    set<int> leafs_index;
    set<int> max_leaf_index;
    for (int u = 0; u < adj_list[v].size(); u++)
    {
        if (!visited[u])
        {
            is_leaf = false;
            pair<int, int> leaf = DFS(adj_list, heights, e, visited, adj_list[v][u]);
            set<int> leafs_index_of_u = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, u);
            leafs_index.insert(leafs_index_of_u.begin(), leafs_index_of_u.end()); // Merge sets
            if (leaf.second > max_leaf.second) // value
            {
                max_leaf.first = leaf.first;
                max_leaf.second = leaf.second;
                max_leaf_index = leafs_index_of_u;
                
            }
        }
    }
    if (max_leaf.second < heights[v])
    {
        e[max_leaf.first] = heights[v];
    }
    leafs_index.erase(max_leaf_index);
    int second_max_index = max(leafs_index.begin(), leafs_index.end());
    if(e[second_max_index] < heights[v])
    {   
        e[second_max_index] = heights[v];

    }
    int sum = accumulate(e.begin(), e.end());
    return sum;
    
    
}
int main()
{
    int n;
    cin >> n;
    vector<int> heights(n + 1);
    vector<int> e(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> heights[i];
    }
    vector<vector<int>> adj_list(n + 1); 
    vector<set<int>> leafs_of_each_one(n + 1);

    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v); 
        adj_list[v].push_back(u); 
    }
    vector<bool> visited(n + 1, false);
    int max_height_index = argmax(heights.begin(), heights.end());
    if (adj_list[max_height_index].size() == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            if (adj_list[i].size() > 1)
            {
                DFS(adj_list, heights, e, visited, i);
                vector<set<int>> &leafs_of_each_node;
                set<int> leafs = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, i);
                leafs.erase(max_height_index);
                int max_leaf = 0;
                int index_leaf = -1;
                for (int leaf:leafs )
                {
                    if (max_leaf < e[leaf])
                    {
                        max_leaf = e[leaf];
                        index_leaf = leaf;
                    } 
                }
                if (max_leaf < heights[max_height_index])
                {
                    e[index_leaf] = heights[max_height_index];
                    int sum = accumulate(e.begin(), e.end());
                    cout << sum << endl;
                    return 0;
                }
                break;
            }
        }
    }
    else
    {
        cout << calc_for_root(leafs_of_each_one, adj_list, heights, e, visited, max_height_index) << endl;

}
