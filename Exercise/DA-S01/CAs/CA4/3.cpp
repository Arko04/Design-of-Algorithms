#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

namespace Graph {

struct Edge {
    int dst;
    int weight;
};

struct Node {
    std::vector<Edge> adj;
};

using type = std::vector<Node>;

} // namespace Graph

constexpr int MAX = std::numeric_limits<int>::max();

std::vector<int> dijkstra(int start, const Graph::type& graph) {
    std::vector<int> dist(graph.size(), MAX);
    std::vector<bool> visited(graph.size(), false);
    dist[start] = 0;

    using DistVtx = std::pair<int, int>;
    std::priority_queue<DistVtx, std::vector<DistVtx>, std::greater<DistVtx>> heap;
    heap.emplace(0, start);

    while (!heap.empty()) {
        const auto x = heap.top();
        heap.pop();

        const int v = x.second;
        // x.first == dist[v]
        visited[v] = true;

        for (const Graph::Edge e : graph[v].adj) {
            if (!visited[e.dst] && dist[v] + e.weight < dist[e.dst]) {
                dist[e.dst] = dist[v] + e.weight;
                heap.emplace(dist[e.dst], e.dst);
            }
        }
    }

    return dist;
}

int solve(int b, const Graph::type& graph) {
    const auto dist = dijkstra(b, graph);
    int max = *std::max_element(dist.begin(), dist.end());
    return (max == MAX) ? -1 : max;
}

int main() {
    int n, m, b;
    std::cin >> n >> m >> b;
    --b;
    Graph::type graph(n);
    for (int i = 0; i < m; ++i) {
        int s1, s2, t;
        std::cin >> s1 >> s2 >> t;
        graph[--s1].adj.push_back({--s2, t});
    }
    std::cout << solve(b, graph);
    return 0;
}
