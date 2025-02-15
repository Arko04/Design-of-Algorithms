#include <iostream>
#include <vector>
#include <set>
#include <numeric>
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
    long max_leaf_index = -1;
    // Iterate through all neighbors of the current node
    for (long long neighbor : adj_list[current_node])
    {
        if (!visited[neighbor])
        {
            isLeaf = false;

            // Set the parent of the neighbor
            parent[neighbor] = current_node;

            // Add neighbor as a child of the current node
            children_map[current_node].push_back(neighbor);

            // Recursively process the neighbor
            int max_leaf_of_neighbor = findChildrenAndLeaves(adj_list, visited, parent, children_map, leaf_sets, neighbor);
            if (e[max_leaf_of_neighbor] > e[max_leaf_index])
            {
                max_leaf_index = max_leaf_of_neighbor;
            }
        }
    }

    // If the current node is a leaf, add it to its own leaf set
    if (isLeaf)
    {
        leaf_sets[current_node].insert(current_node);
        e[current_node] = heights[current_node];
        return current_node;
    }
    else
    {
        // Aggregate all leaf sets from its children
        for (long long child : children_map[current_node])
        {
            leaf_sets[current_node].insert(leaf_sets[child].begin(), leaf_sets[child].end());
        }
        if (e[max_leaf_index] < heights[current_node])
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
    // Reading heights of nodes
    for (long long i = 1; i <= n; ++i)
    {
        cin >> heights[i];
        if(heights[i] > max_height)
        {
            max_height = heights[i];
            max_height_index = i;
        }
    }
    // Adjacency list for the tree
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
    long long max_leaf_index = 0;
    // Start DFS from an arbitrary root (e.g., node 1)
    for (int i = 1; i <= n; i++)
    {

        if (adj_list[i].size() > 1)
        {
            max_leaf_index = findChildrenAndLeaves(adj_list, visited, parent, children_map, leaf_sets, i);
            root = i;
            break;
        }
    }

    // Debug: Print children of each node
    cout << "Children of each node:" << endl;
    for (const auto &entry : children_map)
    {
        cout << "Node " << entry.first << ": ";
        for (long long child : entry.second)
        {
            cout << child << " ";
        }
        cout << endl;
    }

    // Debug: Print leaf sets of each node
    cout << "Leaf sets of each node:" << endl;
    for (const auto &entry : leaf_sets)
    {
        cout << "Node " << entry.first << ": { ";
        for (long long leaf : entry.second)
        {
            cout << "<" << leaf << "," << heights[leaf] << "," << e[leaf] << ">" << " ";
        }
        cout << "}" << endl;
    }
    if (adj_list[max_height_index].size() == 1)
    {
        
    }
    else{
        set<long long>searched_leaf_set;
        for (auto child : children_map[max_height_index])
        {
            // if you found the maximum leaf with e in that set:
            if (leaf_sets[child].find(max_leaf_index)!=leaf_sets[child].end())
            {
                searched_leaf_set = leaf_sets[child];
                break;
            }
        }
        // remove the searched set from our whole set of leaf which is stored in root
        leaf_sets[root].erase(searched_leaf_set.begin(), searched_leaf_set.end());

        // find the next maximum leaf with the highest e value;
        long long second_max_leaf_idnex = 1;
        long long second_max_leaf = 0;
        for (auto leaf : leaf_sets[root])
        {
            if (e[leaf] > second_max_leaf)
            {
                second_max_leaf = e[leaf];
                second_max_leaf_idnex = leaf;
            }
        }
        // update the second maximum leaf with the highest e value to the maximum heights
        if(e[second_max_leaf_idnex] < heights[max_height_index])
        {
            e[second_max_leaf_idnex] = heights[max_height_index];
        }
    }
    return 0;
}
