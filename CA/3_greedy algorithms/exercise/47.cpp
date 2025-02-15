#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;

// Define a struct for a node
struct Node {
    long long index;                 // Index of the node
    long long height;                // Height of the node
    long long e = 0;                     // e value (initially 0)
    set<long long> leaf_set;         // Leaf set of the node
    vector<long long> children;      // Indices of the children

    // Constructor to initialize a Node
    Node(long long i = 0, long long h = 0)
        : index(i), height(h), e(0) {}
};

void findChildrenAndLeaves(
    const vector<vector<long long>> &adj_list,
    vector<bool> &visited,
    vector<long long> &parent,
    vector<Node> &nodes,
    long long current_index)
{
    visited[current_index] = true;
    bool isLeaf = true;

    // Iterate through all neighbors of the current node
    for (long long neighbor : adj_list[current_index]) {
        if (!visited[neighbor]) {
            isLeaf = false;

            // Set the parent of the neighbor
            parent[neighbor] = current_index;

            // Add neighbor as a child of the current node
            nodes[current_index].children.push_back(neighbor);

            // Recursively process the neighbor
            findChildrenAndLeaves(adj_list, visited, parent, nodes, neighbor);
        }
    }

    // If the current node is a leaf, add it to its own leaf set
    if (isLeaf) {
        nodes[current_index].leaf_set.insert(current_index);
    } else {
        // Aggregate all leaf sets from its children
        for (long long child : nodes[current_index].children) {
            nodes[current_index].leaf_set.insert(
                nodes[child].leaf_set.begin(),
                nodes[child].leaf_set.end());
        }
    }
}

int main()
{
    long long n;
    cin >> n;

    // Create a vector of nodes
    vector<Node> nodes(n + 1);

    // Read heights of nodes and initialize their indices
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

    vector<bool> visited(n + 1, false);
    vector<long long> parent(n + 1, -1);

    // Start DFS from an arbitrary root (e.g., a node with more than one neighbor)
    for (int i = 1; i <= n; i++) {
        if (adj_list[i].size() > 1) {
            findChildrenAndLeaves(adj_list, visited, parent, nodes, i);
            break;
        }
    }

    // Debug: Print children of each node
    cout << "Children of each node:" << endl;
    for (long long i = 1; i <= n; ++i) {
        if (!nodes[i].children.empty()) {
            cout << "Node " << i << ": ";
            for (long long child : nodes[i].children) {
                cout << child << " ";
            }
            cout << endl;
        }
    }

    // Debug: Print leaf sets of each node
    cout << "Leaf sets of each node:" << endl;
    for (long long i = 1; i <= n; ++i) {
        if (!nodes[i].leaf_set.empty()) {
            cout << "Node " << i << ": { ";
            for (long long leaf : nodes[i].leaf_set) {
                cout << leaf << " ";
            }
            cout << "}" << endl;
        }
    }

    return 0;
}
