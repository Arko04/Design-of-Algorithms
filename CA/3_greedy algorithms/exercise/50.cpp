#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// Define a struct for a node
struct Node {
    long long height;  // Initial height of the node
    long long cost;    // Minimum cost (e value) for this node
    vector<int> neighbors; // List of connected nodes

    Node(long long h) : height(h), cost(0) {}
};

void dfs(vector<Node>& tree, int u, int parent) {
    if (tree[u].neighbors.size() == 1 && parent != -1) {
        // If it's a leaf, set its cost to its height
        tree[u].cost = tree[u].height;
        return;
    }

    vector<long long> costs;
    for (int v : tree[u].neighbors) {
        if (v == parent) continue;

        dfs(tree, v, u);
        costs.push_back(tree[v].cost);
    }

    // Sort costs to handle the two largest values for non-leaf nodes
    sort(costs.rbegin(), costs.rend());

    if (parent != -1) {
        tree[u].cost = max(tree[u].height, costs[0]); // Max cost to propagate to parent
    } else {
        // For the root, handle the two largest subtrees
        if (costs.size() == 1) {
            tree[u].cost = max(tree[u].height, costs[0]);
        } else {
            tree[u].cost = max(tree[u].height, costs[0] + costs[1] - tree[u].height);
        }
    }
}

long long solve(int n, const vector<long long>& heights, const vector<pair<int, int>>& edges) {
    vector<Node> tree;
    for (auto h : heights) {
        tree.emplace_back(h);
    }

    // Build the adjacency list
    for (auto& edge : edges) {
        int u = edge.first - 1, v = edge.second - 1;
        tree[u].neighbors.push_back(v);
        tree[v].neighbors.push_back(u);
    }

    // Find the root with maximum initial height
    int root = max_element(heights.begin(), heights.end()) - heights.begin();

    // Perform DFS to calculate costs
    dfs(tree, root, -1);

    // Return the total cost
    long long total_cost = 0;
    for (const auto& node : tree) {
        total_cost += node.cost;
    }
    return total_cost;
}

int main() {
    int n;
    cin >> n;

    vector<long long> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    vector<pair<int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    cout << solve(n, heights, edges) << endl;

    return 0;
}
