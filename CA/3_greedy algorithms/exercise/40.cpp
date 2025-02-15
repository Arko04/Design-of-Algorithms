// https://chatgpt.com/share/6745ce1c-4dc0-8003-923c-0ba4c8d89a5a
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <numeric> // For accumulate

using namespace std;

set<long long> DFS_to_find_leaf_set(vector<set<long long>> &leafs_of_each_node, vector<vector<long long>> &adj_list, vector<bool> &visited, long long v) {
    visited[v] = true;
    set<long long> leafs_index;

    bool isLeaf = true; // Assume the node is a leaf
    for (long long u : adj_list[v]) { // Iterate over the neighbors of v
        if (!visited[u]) {
            isLeaf = false;
            set<long long> leafs_index_of_u = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, u);
            leafs_index.insert(leafs_index_of_u.begin(), leafs_index_of_u.end()); // Merge sets
        }
    }

    if (isLeaf) {
        leafs_index.insert(v);
    }

    leafs_of_each_node[v] = leafs_index;
    return leafs_index;
}

pair<long long, long long> DFS(vector<vector<long long>> &adj_list, const vector<long long> &heights, vector<long long> &e, vector<bool> &visited, long long v) {
    visited[v] = true;
    pair<long long, long long> max_leaf = {0, 0};
    bool is_leaf = true;

    for (long long u : adj_list[v]) {
        if (!visited[u]) {
            is_leaf = false;
            pair<long long, long long> leaf = DFS(adj_list, heights, e, visited, u);
            if (leaf.second > max_leaf.second) { // Compare values
                max_leaf = leaf;
            }
        }
    }

    if (is_leaf) {
        e[v] = heights[v];
        return {v, e[v]};
    }

    if (max_leaf.second >= heights[v]) {
        return max_leaf;
    } else {
        e[max_leaf.first] = heights[v];
        return {max_leaf.first, heights[v]};
    }
}

long long calc_for_root(vector<vector<long long>> &adj_list, const vector<long long> &heights, vector<long long> &e, vector<bool> &visited, long long v) {
    visited[v] = true;
    pair<long long, long long> max_leaf = {0, 0};
    bool is_leaf = true;
    set<long long> leafs_index;
    set<long long> max_leaf_index;
    vector<set<long long>> leafs_of_each_node;

    for (long long u : adj_list[v]) {
         vector<bool> visited(heights.size(), false);
        if (!visited[u]) {
            is_leaf = false;
            pair<long long, long long> leaf = DFS(adj_list, heights, e, visited, u);
            vector<bool> visited(heights.size(), false);
            set<long long> leafs_index_of_u = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, u);
            leafs_index.insert(leafs_index_of_u.begin(), leafs_index_of_u.end()); // Merge sets
            if (leaf.second > max_leaf.second) { // Compare values
                max_leaf = leaf;
                max_leaf_index = leafs_index_of_u;
            }
        }
    }

    if (max_leaf.second < heights[v]) {
        e[max_leaf.first] = heights[v];
    }

    for (long long idx : leafs_of_each_node[v]) {
        leafs_index.erase(idx);
    }

    if (!leafs_index.empty()) {
        long long second_max_index = *max_element(leafs_index.begin(), leafs_index.end());
        if (e[second_max_index] < heights[v]) {
            e[second_max_index] = heights[v];
        }
    }

    return accumulate(e.begin(), e.end(), 0); // Sum up e
}

int main() {
    long long n;
    cin >> n;
    vector<long long> heights(n + 1), e(n + 1);
    for (long long i = 1; i <= n; ++i) {
        cin >> heights[i];
    }

    vector<vector<long long>> adj_list(n + 1);
    vector<set<long long>> leafs_of_each_node(n + 1);

    for (long long i = 1; i <= n - 1; ++i) {
        long long u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    auto max_height_index = max_element(heights.begin(), heights.end()) - heights.begin();

    if (adj_list[max_height_index].size() == 1) {
        for (long long i = 1; i <= n; ++i) {
            if (adj_list[i].size() > 1) {
                DFS(adj_list, heights, e, visited, i);
                 vector<bool> visited(n + 1, false);
                set<long long> leafs = DFS_to_find_leaf_set(leafs_of_each_node, adj_list, visited, i);
                leafs.erase(max_height_index);

                long long max_leaf = 0, index_leaf = -1;
                for (long long leaf : leafs) {
                    if (e[leaf] > max_leaf) {
                        max_leaf = e[leaf];
                        index_leaf = leaf;
                    }
                }

                if (max_leaf < heights[max_height_index]) {
                    e[index_leaf] = heights[max_height_index];
                    cout << accumulate(e.begin(), e.end(), 0) << endl;
                    return 0;
                }
                cout << accumulate(e.begin(), e.end(), 0) << endl;
                return 0;
                // break;
            }
        }
    } else {
        cout << calc_for_root( adj_list, heights, e, visited, max_height_index) << endl;
    }

    return 0;
}
