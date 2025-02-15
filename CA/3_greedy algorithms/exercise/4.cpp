// https://chatgpt.com/share/6745b128-8238-8009-a6c0-987b61b4f3fa
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <unordered_map>
using namespace std;

class Node {
public:
    int index; // Node index
    int height; // Initial height `h[i]`
    int e;
    vector<pair<int, int>> children; // Pair of (child index, child height)
    Node* parent; // Pointer to parent
    set<int> leafs_under_this_node; // Set of leaf indices under this node
    pair<int,int> max_leaf_of_branch;

    Node(int idx, int h) : index(idx), height(h), e(0), parent(nullptr) {}
};

class Tree {
public:
    unordered_map<int, Node*> nodes; // Map of nodes by index
    Node* root; // Root of the tree

    Tree(int n, vector<int>& heights, vector<pair<int, int>>& edges) {
        // Initialize nodes with their indices and heights
        for (int i = 1; i <= n; ++i) {
            nodes[i] = new Node(i, heights[i - 1]);
        }

        // Create tree structure based on edges
        for (auto& edge : edges) {
            int u = edge.first, v = edge.second;
            nodes[u]->children.push_back({v, heights[v - 1]});
            nodes[v]->children.push_back({u, heights[u - 1]});
        }

        // Find the root and build the tree
        root = nodes[1]; // Assuming 1 as the root
        buildTree(root, nullptr);
    }

    // Build tree structure by setting parent-child relationships
    void buildTree(Node* current, Node* parent) {
        current->parent = parent;
        vector<pair<int, int>> filteredChildren;

        for (auto& child : current->children) {
            if (parent && child.first == parent->index) continue; // Skip back edge to parent
            filteredChildren.push_back(child);
            buildTree(nodes[child.first], current);
        }

        current->children = filteredChildren; // Update children list to exclude parent
    }

    ~Tree() {
        // Cleanup dynamically allocated nodes
        for (auto& entry : nodes) {
            delete entry.second;
        }
    }

    // Depth-First Search (DFS)
    void dfs(Node* node, function<void(Node*)> process) {
        // Process the current node
        process(node);

        // Recursively visit children
        for (auto& child : node->children) {
            dfs(nodes[child.first], process);
        }
    }

    // Debugging: Print the tree
    void printTree(Node* node = nullptr, int depth = 0) {
        if (!node) node = root;
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << "Node " << node->index << " (Height: " << node->height << ")\n";
        for (auto& child : node->children) {
            printTree(nodes[child.first], depth + 1);
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);

    // Read heights
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    // Read edges
    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    // Build the tree
    Tree tree(n, heights, edges);

    // Debugging: Print the tree structure
    cout << "Tree Structure:\n";
    tree.printTree();

    // Perform DFS and print the node index during traversal
    cout << "\nDFS Traversal:\n";
    tree.dfs(tree.root, [](Node* node) {
        cout << "Visiting Node " << node->index << " (Height: " << node->height << ")\n";
    });

    return 0;
}
