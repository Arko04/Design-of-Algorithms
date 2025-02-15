#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;

// Define a struct for a node
struct Node {
    long long index;            // Index of the node
    long long height;           // Height of the node
    long long e = 0;            // e value (cost for the node)
    Node* max_e_leaf = nullptr; // Pointer to the leaf with the maximum e
    vector<long long> children; // Indices of the children

    Node(long long i, long long h) : index(i), height(h), max_e_leaf(nullptr), e(height){}
    Node() : index(-1), height(0), max_e_leaf(nullptr) {}
};

pair<Node*, long long> DFS_UpdateE(
    const vector<vector<long long>>& adj_list,
    vector<Node>& nodes,
    vector<bool>& visited,
    long long current) {
    visited[current] = true;

    // If the current node is a leaf, set its e value to its height
    if (adj_list[current].size() == 1 && visited[current]) {
        nodes[current].e = nodes[current].height;
        nodes[current].max_e_leaf = &nodes[current];
        return {&nodes[current], nodes[current].e};
    }

    Node* max_leaf_node = nullptr;
    long long max_leaf_height = -1;

    // Traverse neighbors
    for (long long neighbor : adj_list[current]) {
        if (!visited[neighbor]) {
            auto [child_max_leaf, child_max_height] = DFS_UpdateE(adj_list, nodes, visited, neighbor);

            // Update the maximum leaf based on height
            if (child_max_height > max_leaf_height) {
                max_leaf_node = child_max_leaf;
                max_leaf_height = child_max_height;
            }
        }
    }

    // Update the e value for the current node
    if (max_leaf_node) {
        nodes[current].max_e_leaf = max_leaf_node;
        nodes[current].e = max(nodes[current].height, nodes[max_leaf_node->index].e);
    }

    return {max_leaf_node, nodes[current].e};
}

long long calculateLeafESum(const vector<Node>& nodes) {
    long long sum = 0;

    // Iterate over all nodes and add the e value of the leaves
    for (const auto& node : nodes) {
        if (node.children.empty()) {
            sum += node.e;
        }
    }

    return sum;
}

int main() {
    long long n;
    cin >> n;

    vector<Node> nodes(n + 1);

    // Read heights of nodes and initialize them
    for (long long i = 1; i <= n; ++i) {
        long long height;
        cin >> height;
        nodes[i] = Node(i, height);
    }

    // Adjacency list for the tree
    vector<vector<long long>> adj_list(n + 1);
    for (long long i = 1; i < n; ++i) {
        long long u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    // Find the root (choose any node with degree > 1)
    long long root = 1;
    for (long long i = 1; i <= n; ++i) {
        if (adj_list[i].size() > 1) {
            root = i;
            break;
        }
    }

    vector<bool> visited(n + 1, false);

    // Start DFS to calculate e values
    DFS_UpdateE(adj_list, nodes, visited, root);

    // Calculate and output the total sum of e values
    cout << calculateLeafESum(nodes) << endl;

    return 0;
}
