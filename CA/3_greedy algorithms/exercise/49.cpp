#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;

// Define a struct for a node
struct Node
{
    long long index;            // Index of the node
    long long height;           // Height of the node
    long long e = 0;            // e value (for leaf nodes)
    Node *max_e_leaf = nullptr; // Pointer to the leaf with the maximum e
    set<long long> leaf_set;    // Leaf set of the node
    vector<long long> children; // Indices of the children

    Node(long long i, long long h) : index(i), height(h), max_e_leaf(nullptr), e(height) {}
    Node() : index(-1), height(0), max_e_leaf(nullptr) {}
};

void updateLeafSetAndHeight(
    vector<Node> &nodes, 
    vector<vector<long long>> &adj_list, 
    vector<long long> &heights, 
    vector<bool> &visited, 
    long long root_index) 
{
    // Step 1: Find the node with the maximum height
    long long max_height_node = root_index;
    for (long long i = 1; i <= nodes.size(); ++i) {
        if (nodes[i].height > nodes[max_height_node].height) {
            max_height_node = i;
        }
    }

    // Step 2: Find the leaf set of the max height node
    set<long long>& max_height_leaf_set = nodes[max_height_node].leaf_set;

    // Step 3: Remove the leaf set of the node with max height from the root's leaf set
    set<long long>& root_leaf_set = nodes[root_index].leaf_set;

    // Remove the max height leaf set from the root's leaf set
    for (long long leaf : max_height_leaf_set) {
        root_leaf_set.erase(leaf);
    }

    // Step 4: Now find the leaf with the maximum `e` from the remaining root's leaf set
    long long max_e_leaf = *root_leaf_set.begin();
    for (long long leaf : root_leaf_set) {
        if (nodes[leaf].e > nodes[max_e_leaf].e) {
            max_e_leaf = leaf;
        }
    }

    // Step 5: Update the root's `e` value to the maximum height of the remaining leaf set
    nodes[root_index].e = max(heights[max_e_leaf],nodes[root_index].e);
}

long long calculateLeafESum(const vector<Node> &nodes) {
    long long sum = 0;

    // Iterate over all nodes
    for (long long i = 1; i < nodes.size(); ++i) {
        // Check if the node is a leaf (it has no children)
        if (nodes[i].children.empty()) {
            // Add the `e` value of the leaf node to the sum
            sum += nodes[i].e;
        }
    }

    return sum;
}

pair<Node *, long long> DFS_UpdateE(
    const vector<vector<long long>> &adj_list,
    vector<Node> &nodes,
    vector<bool> &visited,
    long long current)
{
    visited[current] = true;

    // If the current node is a leaf, set its e value to its height
    if (nodes[current].children.empty() && adj_list[current].size() == 1)
    {
        nodes[current].e = nodes[current].height;
        nodes[current].max_e_leaf = &nodes[current];
        // return {&nodes[current], nodes[current].e};
    }

    Node *max_leaf_node = nullptr;
    long long max_leaf_height = -1;

    // Traverse neighbors
    for (long long neighbor : adj_list[current])
    {
        if (!visited[neighbor])
        {
            // Recursive DFS call for the child node
            auto [child_max_leaf, child_max_height] = DFS_UpdateE(adj_list, nodes, visited, neighbor);

            // Update the maximum leaf based on the height
            if (child_max_height > max_leaf_height)
            {
                max_leaf_node = child_max_leaf;
                max_leaf_height = child_max_height;
            }
        }
    }

    // Update the current node's max_e_leaf to point to the max leaf in its subtree
    nodes[current].max_e_leaf = max_leaf_node;

    return {max_leaf_node, max_leaf_height};
}

void propagateE(
    const vector<vector<long long>> &adj_list,
    vector<Node> &nodes,
    long long root)
{
    vector<bool> visited(nodes.size(), false);

    // Start DFS to calculate and propagate `e`
    DFS_UpdateE(adj_list, nodes, visited, root);
}

int main()
{
    long long n;
    cin >> n;

    // Create a vector of nodes
    vector<Node> nodes(n + 1);
    int max_height_index = 0;
    int max_height = 0;
    // Read heights of nodes and initialize their indices
    for (long long i = 1; i <= n; ++i)
    {
        long long height;
        cin >> height;
        if(height > max_height)
        {
            max_height = height;
            max_height_index = i;
        }
        nodes[i] = Node(i, height);
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

    // Find root (arbitrary or based on a condition)
    long long root = max_height_index;
    // for (int i = 1; i <= n; ++i)
    // {
    //     if (adj_list[i].size() > 1)
    //     {
    //         root = i;
    //         break;
    //     }
    // }

    // Compute `e` values and `max_e_leaf`
    propagateE(adj_list, nodes, root);

    // Calculate and output the sum of `e` values of the leaf nodes
    cout << calculateLeafESum(nodes) << endl;

    return 0;
}
