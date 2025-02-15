#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;
vector<set<long long>> DFS_to_find_leaf_set(vector<vector<set<long long>>> &leafs_of_each_node, const vector<vector<long long>> &adj_list, vector<bool> &visited, long long v)
{
    visited[v] = true;
    vector<set<long long>> leafs_index;

    bool isLeaf = true;

    // Iterate through all the adjacent nodes (neighbors) of the current node
    for (long long u : adj_list[v])
    {
        if (!visited[u])
        {
            isLeaf = false;
            // Perform DFS on the child node to collect its leaf sets
            vector<set<long long>> leafs_index_of_u = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, u);

            // Now merge the leaf sets from this child node
            for (const auto &leafSet : leafs_index_of_u)
            {
                leafs_index.push_back(leafSet);
            }
        }
    }

    // If the current node is a leaf (no unvisited neighbors), store it
    if (isLeaf)
    {
        set<long long> leafSet;
        leafSet.insert(v); // The node itself is a leaf
        leafs_index.push_back(leafSet);
    }

    // Store the merged leaf sets for the current node
    leafs_of_each_node[v] = leafs_index;

    // Return the merged leaf sets for this node
    return leafs_index;
}

pair<long long, long long> DFS(const vector<vector<long long>> &adj_list, const vector<long long> &heights, vector<long long> &e, vector<bool> &visited, long long v)
{
    visited[v] = true;
    pair<long long, long long> max_leaf = {0, 0};
    bool is_leaf = true;

    for (long long u : adj_list[v])
    {
        if (!visited[u])
        {
            is_leaf = false;
            pair<long long, long long> leaf = DFS(adj_list, heights, e, visited, u);
            if (leaf.second > max_leaf.second)
            {
                max_leaf = leaf;
            }
        }
    }

    if (is_leaf)
    {
        e[v] = heights[v];
        return {v, e[v]};
    }

    if (max_leaf.second >= heights[v])
    {
        return max_leaf;
    }
    else
    {
        e[max_leaf.first] = heights[v];
        return {max_leaf.first, heights[v]};
    }
}

long long calc_for_root(const vector<vector<long long>> &adj_list, const vector<long long> &heights, vector<long long> &e, vector<bool> &visited, long long v)
{
    visited[v] = true;
    pair<long long, long long> max_leaf = {0, 0};
    set<long long> leafs_index;
    vector<vector<set<long long>>> leafs_of_each_node(e.size());
    vector<set<long long>> leafs_index_of_v = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, v);
    fill(visited.begin(), visited.end(), false);
    if (adj_list[v].size() == 1)
    {
        for (long long u : adj_list[v])
        {
            if (!visited[u])
            {
                pair<long long, long long> leaf = DFS(adj_list, heights, e, visited, u);
                // leafs_index.insert(leafs_index_of_u.begin(), leafs_index_of_u.end());
                if (leaf.second > max_leaf.second)
                {
                    max_leaf = leaf;
                }
            }
        }

        if (max_leaf.second < heights[v])
        {
            e[max_leaf.first] = heights[v];
        }
    }
    else
    {
        for (int i = 0; i < leafs_of_each_node[v].size(); i++)
        {
            if (v in leafs_of_each_node[v][i])
            {
                leafs_index_of_v.erase(leafs_of_each_node[v][i]);
                leafs_index_of_v.erase(v);
                long long second_max_index = *max_element(leafs_index_of_v.begin(), leafs_index_of_v.end());
                if (e[second_max_index] < heights[v])
                {
                    e[second_max_index] = heights[v];
                }
            }
        }
    }

    // for (long long idx : leafs_of_each_node[v]) {
    //     leafs_index_of_v.erase(idx);
    // }

    // if (!leafs_index_of_v.empty())
    // {
    //     long long second_max_index = *max_element(leafs_index_of_v.begin(), leafs_index_of_v.end());
    //     if (e[second_max_index] < heights[v])
    //     {
    //         e[second_max_index] = heights[v];
    //     }
    // }

    return accumulate(e.begin(), e.end(), 0LL);
}

int main()
{
    long long n;
    cin >> n;
    vector<long long> heights(n + 1), e(n + 1);
    for (long long i = 1; i <= n; ++i)
    {
        cin >> heights[i];
    }

    vector<vector<long long>> adj_list(n + 1);
    vector<set<long long>> leafs_of_each_node(n + 1);

    for (long long i = 1; i < n; ++i)
    {
        long long u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    auto max_height_index = max_element(heights.begin(), heights.end()) - heights.begin();
    vector<bool> visited(n + 1, false);
    visited[0] = true;

    // if (adj_list[max_height_index].size() == 1) {
    //     for (long long i = 1; i <= n; ++i) {
    //         if (adj_list[i].size() > 1) {
    //             set<long long> leafs = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, i);
    //             fill(visited.begin(), visited.end(), false);
    //             pair<int, int> maximum_leaf = DFS(adj_list, heights, e, visited, i);
    //             leafs.erase(maximum_leaf.first);

    //             long long max_leaf = 0, index_leaf = -1;
    //             for (long long leaf : leafs) {
    //                 if (e[leaf] > max_leaf) {
    //                     max_leaf = e[leaf];
    //                     index_leaf = leaf;
    //                 }
    //             }

    //             if (max_leaf < heights[max_height_index]) {
    //                 e[index_leaf] = heights[max_height_index];
    //             }
    //             cout << accumulate(e.begin(), e.end(), 0LL) << endl;
    //             return 0;
    //         }
    //     }
    // } else {
    // fill(visited.begin(), visited.end(), false);
    cout << calc_for_root(adj_list, heights, e, visited, max_height_index) << endl;
    // }

    return 0;
}
