#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;


vector<set<long long>> DFS_to_find_leaf_set(
    vector<vector<set<long long>>> &leafs_of_each_node, 
    const vector<vector<long long>> &adj_list,  
    vector<bool> &visited, 
    long long v
) {
    visited[v] = true;
    vector<set<long long>> leafs_index;

    bool isLeaf = true;

    // Iterate through all the adjacent nodes (neighbors) of the current node
    for (long long u : adj_list[v]) {
        if (!visited[u]) {
            isLeaf = false;
            // Perform DFS on the child node to collect its leaf sets
            vector<set<long long>> leafs_index_of_u = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, u);

            // Now merge the leaf sets from this child node
            for (const auto &leafSet : leafs_index_of_u) {
                leafs_index.push_back(leafSet);
            }
        }
    }

    // If the current node is a leaf (no unvisited neighbors), store it
    if (isLeaf) {
        set<long long> leafSet;
        leafSet.insert(v); // The node itself is a leaf
        leafs_index.push_back(leafSet);
    }

    // Store the merged leaf sets for the current node
    leafs_of_each_node[v] = leafs_index;

    // Return the merged leaf sets for this node
    return leafs_index;
}

pair<long long, long long> DFS(
    const vector<vector<long long>> &adj_list, 
    const vector<long long> &heights, 
    vector<long long> &e, 
    vector<bool> &visited, 
    long long v
) {
    visited[v] = true;
    pair<long long, long long> max_leaf = {v, heights[v]};  // Store node and its height

    bool is_leaf = true;

    for (long long u : adj_list[v]) {
        if (!visited[u]) {
            is_leaf = false;
            pair<long long, long long> leaf = DFS(adj_list, heights, e, visited, u);
            if (leaf.second > max_leaf.second) {
                max_leaf = leaf;
            }
        }
    }

    if (is_leaf) {
        e[v] = heights[v];
        return {v, e[v]};
    }

    return max_leaf;
}

long long calc_for_root(
    const vector<vector<long long>> &adj_list, 
    const vector<long long> &heights, 
    vector<long long> &e, 
    vector<bool> &visited, 
    long long v
) {
    visited[v] = true;
    pair<long long, long long> max_leaf = {v, heights[v]}; // To store maximum leaf found
    vector<vector<set<long long>>> leafs_of_each_node(e.size());
    vector<set<long long>> leafs_index_of_v = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, v);

    // Now propagate values
    fill(visited.begin(), visited.end(), false);
    
    if (adj_list[v].size() == 1) {
        // Only one child, process directly
        for (long long u : adj_list[v]) {
            if (!visited[u]) {
                pair<long long, long long> leaf = DFS(adj_list, heights, e, visited, u);
                if (leaf.second > max_leaf.second) {
                    max_leaf = leaf;
                }
            }
        }

        // Adjust the value of the node based on the leaf heights
        if (max_leaf.second < heights[v]) {
            e[max_leaf.first] = heights[v];
        }
    } else {
        // Handle general case where node has multiple children
        for (const auto& leafSet : leafs_index_of_v) {
            for (long long leaf : leafSet) {
                if (e[leaf] < heights[v]) {
                    e[leaf] = heights[v];
                }
            }
        }
    }

    // Return the accumulated sum of values in e
    return accumulate(e.begin(), e.end(), 0LL);
}

int main() {
    long long n;
    cin >> n;
    
    vector<long long> heights(n + 1), e(n + 1, 0);
    
    // Reading heights of nodes
    for (long long i = 1; i <= n; ++i) {
        cin >> heights[i];
    }

    // Adjacency list for the tree
    vector<vector<long long>> adj_list(n + 1);
    for (long long i = 1; i < n; ++i) {
        long long u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    // Find the node with maximum height
    auto max_height_index = max_element(heights.begin(), heights.end()) - heights.begin();
    
    // Initialize visited array
    vector<bool> visited(n + 1, false);
    visited[0] = true;

    // Calculate the result starting from the node with the maximum height
    cout << calc_for_root(adj_list, heights, e, visited, max_height_index) << endl;

    return 0;
}
