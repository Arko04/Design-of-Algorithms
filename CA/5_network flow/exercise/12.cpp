// https://chatgpt.com/share/678b6f5b-39d0-8003-b5a8-0579b100ba4f
#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

const int INF = 1000000000; // A large value to represent infinity
const int k = 1000;         // Maximum number of nodes
int f[k][k];                // Flow matrix
int c[k][k];                // Capacity matrix

// Depth-First Search to find augmenting paths
void dfs_ford_fulkerson(vector<set<int>> &outgoing, vector<set<int>> &incoming, vector<int> &flow, vector<int> &parent, int u, int x)
{
    flow[u] = x; // Update flow for the current node
    for (int v : outgoing[u])
    { // Explore outgoing edges
        if (flow[v] == -1 && c[u][v] - f[u][v] > 0)
        {                  // Check for residual capacity
            parent[v] = u; // Update parent
            dfs_ford_fulkerson(outgoing, incoming, flow, parent, v, min(x, c[u][v] - f[u][v]));
        }
    }
    for (int v : incoming[u])
    { // Explore incoming edges
        if (flow[v] == -1 && f[v][u] > 0)
        {                  // Check for reverse flow
            parent[v] = u; // Update parent
            dfs_ford_fulkerson(outgoing, incoming, flow, parent, v, min(x, f[v][u]));
        }
    }
}

// Ford-Fulkerson algorithm for Maximum Flow
int ford_fulkerson(vector<set<int>> &outgoing, vector<set<int>> &incoming, int n, int source, int sink)
{
    memset(f, 0, sizeof(f));        // Initialize flow matrix
    vector<int> flow(n), parent(n); // Flow and parent tracking

    int max_flow = 0;

    while (true)
    {
        fill(flow.begin(), flow.end(), -1);                                // Reset flow for each iteration
        dfs_ford_fulkerson(outgoing, incoming, flow, parent, source, INF); // Find augmenting path

        if (flow[sink] == -1)
        { // No more augmenting paths
            break;
        }

        int v = sink, path_flow = flow[sink];
        max_flow += path_flow;

        // Update the residual graph
        while (v != source)
        {
            int u = parent[v];
            f[u][v] += path_flow; // Forward flow
            f[v][u] -= path_flow; // Reverse flow
            v = u;
        }
    }

    return max_flow;
}

// Function to add edges to the graph
void add_edge(vector<set<int>> &outgoing, vector<set<int>> &incoming, int u, int v, int capacity)
{
    if (capacity == 0)
    {
        return;
    }
    if (c[u][v] == 0)
    {
        outgoing[u].insert(v);
        incoming[v].insert(u);
        c[u][v] = capacity;
        // cout << "edge from: " << u << " to " << v << " with cap " << c[u][v] << " is added" << endl;
    }
    else
    {
        if (u == 0 || v == 1)
        {
            c[u][v] += capacity;
            // cout << "edge from: " << u << " to " << v << " now with cap " << c[u][v] << " is updated" << endl;
        }
        else
        {
        }
    }
}

int main()
{
    int n;
    cin >> n;

    memset(c, 0, sizeof(c)); // Initialize all elements to 0
    vector<string> grid(2 * n - 1);
    for (int i = 0; i < 2 * n - 1; i++)
    {
        cin >> grid[i];
    }

    vector<set<int>> outgoing(k), incoming(k); // Adjacency lists

    // Source and sink
    int source = 0, sink = 1;
    int node_offset = 2; // Nodes start after source and sink

    // Map grid centers to graph nodes
    vector<vector<int>> node_map(n, vector<int>(n, 0));
    int node_count = 0;

    for (int i = 1; i < 2 * n - 2; i += 2)
    {
        for (int j = 1; j < 2 * n - 2; j += 2)
        {
            node_map[(i - 1) / 2][(j - 1) / 2] = node_offset + node_count++;
        }
    }

    // Add edges based on the grid
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            int current_node = node_map[i][j];
            int edges = 0;

            // Count the number of edges around the center
            if (grid[2 * i][2 * j + 1] == '-')
                edges++; // Top edge
            if (grid[2 * i + 2][2 * j + 1] == '-')
                edges++; // Bottom edge
            if (grid[2 * i + 1][2 * j] == '|')
                edges++; // Left edge
            if (grid[2 * i + 1][2 * j + 2] == '|')
                edges++; // Right edge

            int remaining_capacity = 3 - edges; // Remaining edges that can be drawn
            // cout << "for:(" << i << ", " << j << ") we have: " << remaining_capacity << endl;
            if ((i + j) % 2 == 0)
            {
                // Left partition
                add_edge(outgoing, incoming, source, current_node, remaining_capacity);

                if (i > 0)
                    add_edge(outgoing, incoming, current_node, node_map[i - 1][j], 1); // Up
                if (i == 0 && grid[2 * i][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, current_node, sink, 1);
                if (i < n - 2)
                    add_edge(outgoing, incoming, current_node, node_map[i + 1][j], 1); // Down
                if (i == n - 2 && grid[2 * i + 2][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, current_node, sink, 1);
                if (j > 0)
                    add_edge(outgoing, incoming, current_node, node_map[i][j - 1], 1); // Left
                if (j == 0 && grid[2 * i + 1][2 * j] != '|')
                    add_edge(outgoing, incoming, current_node, sink, 1);
                if (j < n - 2)
                    add_edge(outgoing, incoming, current_node, node_map[i][j + 1], 1); // Right
                if (j == n - 2 && grid[2*i+1][2*j + 2] != '|')
                    add_edge(outgoing, incoming, current_node, sink, 1);
            }
            else
            {
                // Right partition
                add_edge(outgoing, incoming, current_node, sink, remaining_capacity);

                if (i > 0)
                    add_edge(outgoing, incoming, node_map[i - 1][j], current_node, 1); // Up
                if (i == 0 && grid[2 * i][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, source, current_node, 1);
                if (i < n - 2)
                    add_edge(outgoing, incoming, node_map[i + 1][j], current_node, 1); // Down
                if (i == n - 2 && grid[2 * i + 2][2 * j + 1] != '-')
                    add_edge(outgoing, incoming, source, current_node, 1);
                if (j > 0)
                    add_edge(outgoing, incoming, node_map[i][j - 1], current_node, 1); // Left
                if (j == 0 && grid[2 * i + 1][2 * j] != '|')
                    add_edge(outgoing, incoming, source, current_node, 1);
                if (j < n - 2)
                    add_edge(outgoing, incoming, node_map[i][j + 1], current_node, 1); // Right
                if (j == n - 2 && grid[2*i+1][2*j + 2] != '|')
                    add_edge(outgoing, incoming, source, current_node, 1);
            }

            // // Connect to adjacent nodes
            // if (i > 0)
            //     add_edge(outgoing, incoming, current_node, node_map[i - 1][j], 1); // Up

            // if (i == 0)
            // {
            //     if ((i + j) % 2 == 0)
            //     {
            //         add_edge(outgoing, incoming, current_node, sink, 1);
            //     }
            //     else
            //     {
            //         add_edge(outgoing, incoming, source, current_node, 1);
            //     }
            // }
            // if (i < n - 2)
            //     add_edge(outgoing, incoming, current_node, node_map[i + 1][j], 1); // Down

            // if (i == n - 2)
            // {
            //     if ((i + j) % 2 == 0)
            //     {
            //         add_edge(outgoing, incoming, current_node, sink, 1);
            //     }
            //     else
            //     {
            //         add_edge(outgoing, incoming, source, current_node, 1);
            //     }
            // }
            // if (j > 0)
            //     add_edge(outgoing, incoming, current_node, node_map[i][j - 1], 1); // Left

            // if (j == 0)
            // {
            //     if ((i + j) % 2 == 0)
            //     {
            //         add_edge(outgoing, incoming, current_node, sink, 1);
            //     }
            //     else
            //     {
            //         add_edge(outgoing, incoming, source, current_node, 1);
            //     }
            // }
            // if (j < n - 2)
            //     add_edge(outgoing, incoming, current_node, node_map[i][j + 1], 1); // Right

            // if (j == n - 2)
            // {
            //     if ((i + j) % 2 == 0)
            //     {
            //         add_edge(outgoing, incoming, current_node, sink, 1);
            //     }
            //     else
            //     {
            //         add_edge(outgoing, incoming, source, current_node, 1);
            //     }
            // }
        }
    }

    // Calculate maximum flow
    int max_flow = ford_fulkerson(outgoing, incoming, node_offset + node_count, source, sink);
    cout << max_flow << endl;

    return 0;
}
