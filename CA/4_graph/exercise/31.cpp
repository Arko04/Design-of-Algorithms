// // // https://chatgpt.com/share/676ad7c0-18d4-8003-baa8-ed6059fe2cf0
// // // https://chatgpt.com/share/676ad9a3-ca70-8003-9312-f2d5dcb78cd4
// // #include <iostream>
// // #include <vector>
// // #include <utility>
// // using namespace std;

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <set>
// using namespace std;

// struct Edge
// {
//     int u, v, weight;
//     bool operator<(const Edge &other) const
//     {
//         return weight < other.weight;
//     }
// };


// void dfs(int curr, int target, vector<pair<int, int>> adj[], vector<int>& path, vector<bool>& visited, vector<pair<int, int>>& edges) {
//     if (curr == target) return;

//     visited[curr] = true;
//     for (auto& [next, weight] : adj[curr]) {
//         if (!visited[next]) {
//             path.push_back(next);
//             edges.push_back({curr, weight}); // Store edge and its weight
//             dfs(next, target, adj, path, visited, edges);
//             if (path.back() == target) return; // Stop if target is reached
//             path.pop_back(); // Backtrack
//             edges.pop_back();
//         }
//     }
// }

// struct UnionFind
// {
//     vector<int> parent, rank;

//     UnionFind(int n)
//     {
//         parent.resize(n);
//         rank.resize(n, 0);
//         for (int i = 0; i < n; ++i)
//             parent[i] = i;
//     }

//     int find(int u)
//     {
//         if (parent[u] != u)
//             parent[u] = find(parent[u]); // Path compression
//         return parent[u];
//     }

//     bool union_sets(int u, int v)
//     {
//         int root_u = find(u);
//         int root_v = find(v);
//         if (root_u != root_v)
//         {
//             if (rank[root_u] < rank[root_v])
//             {
//                 swap(root_u, root_v);
//             }
//             parent[root_v] = root_u;
//             if (rank[root_u] == rank[root_v])
//             {
//                 rank[root_u]++;
//             }
//             return true;
//         }
//         return false;
//     }
// };

// int main()
// {
//     int n, m;
//     cin >> n >> m;
//     // create adj list
//     vector<Edge> edges(m);
//     all the adges initialzed with "any"
//     for (int i = 0; i < m; ++i)
//     {
//         cin >> edges[i].u >> edges[i].v >> edges[i].weight;
//         edges[i].u--; // Convert to 0-based indexing
//         edges[i].v--;
//         // update adj list
//     }

//     // Step 1: Sort edges by weight
//     sort(edges.begin(), edges.end());

//     // Step 2: Kruskal's Algorithm
//     UnionFind uf(n);
//     vector<Edge> mst;

//     // int mst_weight = 0;

//     for (const auto &edge : edges)
//     {
//         if (uf.union_sets(edge.u, edge.v))
//         {
//             mst.push_back(edge);
//             // mst_weight += edge.weight;
//             if (mst.size() == n - 1)
//                 break; // MST has n-1 edges
//         }
//     }
//     cout << "---------------" << endl;
//     set<Edge> mst_copy(mst.begin(), mst.end());
//     // Output the MST
//     // cout << "MST Weight: " << mst_weight << endl;
//     // cout << "Edges in the MST:" << endl;
//     for (const auto &edge : mst)
//     {
//         cout << edge.u + 1 << " " << edge.v + 1 << " " << edge.weight << endl; // Convert back to 1-based indexing
//     }

//     for (int i = 0; i < m; i++)
//     {
//         if edges[i] in mst_copy:
//             continue;
//         int u = edges[i].u;
//         int v = edges[i].v;
//         int weight = edges[i].wieght;
//           vector<bool> visited(n+1, false);

//          dfs(u, v, adj, path, visited, edges);
//          for (edges searched_edges : path)
//             if (weigth == searched_edges.wights)
//                 that searched_edge should be "at least one"
//                 our edge also should be "at least one"
//         if (none wight == our wight)
//                 our eage is "none"
        
//     }
    
//     return 0;
// }
