// https://chatgpt.com/share/6746f8a7-8140-8009-b172-f74588b012e0
// https://chatgpt.com/share/6746f8de-be74-8009-9dc1-88393344b0c6
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<long long, long long> e;
unordered_map<long long, long long> heights;

long long findChildrenAndLeaves(
    const vector<vector<long long>> &adj_list,
    vector<bool> &visited,
    vector<long long> &parent,
    unordered_map<long long, vector<long long>> &children_map,
    unordered_map<long long, set<long long>> &leaf_sets,
    long long current_node)
{
    visited[current_node] = true;
    bool isLeaf = true;
    long long max_leaf_index = -1;
    long long max_leaf_value = 0;

    for (long long neighbor : adj_list[current_node])
    {
        if (!visited[neighbor])
        {
            isLeaf = false;
            parent[neighbor] = current_node;
            children_map[current_node].push_back(neighbor);

            long long max_leaf_of_neighbor = findChildrenAndLeaves(adj_list, visited, parent, children_map, leaf_sets, neighbor);
            if (e[max_leaf_of_neighbor] > max_leaf_value)
            {
                max_leaf_index = max_leaf_of_neighbor;
                max_leaf_value = e[max_leaf_of_neighbor];
            }
        }
    }

    if (isLeaf)
    {
        leaf_sets[current_node].insert(current_node);
        e[current_node] = heights[current_node];
        return current_node;
    }
    else
    {
        for (long long child : children_map[current_node])
        {
            leaf_sets[current_node].insert(leaf_sets[child].begin(), leaf_sets[child].end());
        }
        if (max_leaf_index != -1 && e[max_leaf_index] < heights[current_node])
        {
            e[max_leaf_index] = heights[current_node];
        }
        return max_leaf_index;
    }
}

int main()
{
    long long n;
    cin >> n;

    long long max_height_index = -1;
    long long max_height = 0;

    for (long long i = 1; i <= n; ++i)
    {
        cin >> heights[i];
        if (heights[i] > max_height)
        {
            max_height = heights[i];
            max_height_index = i;
        }
    }

    vector<vector<long long>> adj_list(n + 1);
    for (long long i = 1; i < n; ++i)
    {
        long long u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    vector<long long> parent(n + 1, -1);
    unordered_map<long long, vector<long long>> children_map;
    unordered_map<long long, set<long long>> leaf_sets;

    long long root = 1;
    long long max_leaf_index = -1;

    for (long long i = 1; i <= n; i++)
    {
        if (adj_list[i].size() > 1)
        {
            max_leaf_index = findChildrenAndLeaves(adj_list, visited, parent, children_map, leaf_sets, i);
            root = i;
            break;
        }
    }

    // cout << "max_leaf_index is: " << max_leaf_index << endl;
    // cout << "Children of each node:" << endl;
    // for (const auto &entry : children_map)
    // {
    //     cout << "Node " << entry.first << ": ";
    //     for (long long child : entry.second)
    //     {
    //         cout << child << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Leaf sets of each node:" << endl;
    // for (const auto &entry : leaf_sets)
    // {
    //     cout << "Node " << entry.first << ": { ";
    //     for (long long leaf : entry.second)
    //     {
    //         cout << "<" << leaf << "," << heights[leaf] << "," << e[leaf] << "> ";
    //     }
    //     cout << "}" << endl;
    // }

    long long sum = 0;
    if (adj_list[max_height_index].size() == 1)
    {
        sum += e[max_leaf_index];
        leaf_sets[root].erase(max_leaf_index);
    }
    else
    {
        for (auto child : children_map[max_height_index])
        {
            if (leaf_sets[child].find(max_leaf_index) != leaf_sets[child].end())
            {
                for (auto leaf : leaf_sets[child])
                {
                    sum += e[leaf];
                    leaf_sets[root].erase(leaf);
                }
                break;
            }
        }
    }

    long long second_max_leaf_index = -1;
    long long second_max_leaf_value = 0;
    for (auto leaf : leaf_sets[root])
    {
        if (e[leaf] > second_max_leaf_value)
        {
            second_max_leaf_value = e[leaf];
            second_max_leaf_index = leaf;
        }
    }

    // cout << "second max_leaf_index is: " << second_max_leaf_index << endl;
    if (second_max_leaf_index != -1 && e[second_max_leaf_index] < heights[max_height_index])
    {
        e[second_max_leaf_index] = heights[max_height_index];
    }
    // cout << "Leaf sets of each node:" << endl;
    // for (const auto &entry : leaf_sets)
    // {
    //     cout << "Node " << entry.first << ": { ";
    //     for (long long leaf : entry.second)
    //     {
    //         cout << "<" << leaf << "," << heights[leaf] << "," << e[leaf] << "> ";
    //     }
    //     cout << "}" << endl;
    // }
    for (auto leaf : leaf_sets[root])
    {
        sum += e[leaf];
    }
    cout << sum << endl;
    return 0;
}
