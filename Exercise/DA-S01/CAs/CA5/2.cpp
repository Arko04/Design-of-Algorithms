#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

namespace Graph {

struct Edge {
    int src;
    int dst;
    int type;
    int flow;
    int capacity;
    int revIdx;

    void nullify() { src = dst = type = flow = capacity = -1; }
    bool null() const { return (src == -1) && (dst == -1) && (type == -1) && (flow == -1) && (capacity == -1); }
};

enum class State {
    notseen,
    seen,
    completed,
};

struct Node {
    std::vector<Edge> adj;
    State state = State::notseen;
};

using type = std::vector<Node>;

} // namespace Graph

namespace cycles {

void DFS(Graph::type& graph,
         int node,
         int parent,
         std::vector<Graph::Edge>& parents,
         std::vector<std::vector<int>>& components) {
    graph[node].state = Graph::State::seen;

    for (auto edge : graph[node].adj) {
        if (edge.dst == parent) continue;
        if (graph[edge.dst].state == Graph::State::notseen) {
            parents[edge.dst] = edge;
            DFS(graph, edge.dst, node, parents, components);
        }
        else if (graph[edge.dst].state == Graph::State::seen) {
            std::vector<int> cycleType;
            cycleType.push_back(edge.type);
            Graph::Edge e = edge;
            while (e.src != edge.dst) {
                Graph::Edge ep = parents[e.src];
                cycleType.push_back(ep.type);
                parents[e.src].nullify();
                e = ep;
            }
            components.push_back(std::move(cycleType));
        }
    }

    graph[node].state = Graph::State::completed;
}

std::vector<std::vector<int>> getComponents(Graph::type&& graph) {
    std::vector<std::vector<int>> components;

    std::vector<Graph::Edge> parents(graph.size());
    parents.front().nullify();

    DFS(graph, 0, -1, parents, components);

    for (auto parentEdge : parents) {
        if (parentEdge.null()) continue;
        components.push_back(std::vector<int> {parentEdge.type});
    }

    return components;
}

} // namespace cycles

namespace dinic {

int DFS(Graph::type& graph, std::vector<int>& edgeCnt, std::vector<int>& dist, int s, int t, int flow) {
    if (s == t) return flow;

    while (edgeCnt[s] < graph[s].adj.size()) {
        Graph::Edge& edge = graph[s].adj[edgeCnt[s]];
        if (dist[edge.dst] == dist[s] + 1 && // not backwards
            edge.flow < edge.capacity) {
            int newFlow = DFS(graph, edgeCnt, dist, edge.dst, t, std::min(flow, edge.capacity - edge.flow));
            if (newFlow > 0) {
                edge.flow += newFlow;
                graph[edge.dst].adj[edge.revIdx].flow -= newFlow;
                return newFlow;
            }
        }
        ++edgeCnt[s];
    }

    return 0;
}

void BFS(Graph::type& graph, int s, int t, std::vector<int>& dist) {
    std::fill(dist.begin(), dist.end(), -1);
    dist[s] = 0;

    std::queue<int> queue;
    queue.push(s);

    while (!queue.empty()) {
        const auto node = queue.front();
        queue.pop();

        for (const Graph::Edge edge : graph[node].adj) {
            if (dist[edge.dst] < 0 && edge.flow < edge.capacity) {
                dist[edge.dst] = dist[node] + 1;
                queue.push(edge.dst);
            }
        }
    }
}

int maxFlow(Graph::type& graph, int s, int t) {
    int maxFlow = 0;
    std::vector<int> dist(graph.size(), -1);

    while (true) {
        BFS(graph, s, t, dist);
        if (dist[t] == -1) break;

        std::vector<int> edgeCnt(graph.size(), 0);
        int newFlow = -1;
        while (newFlow != 0) {
            newFlow = DFS(graph, edgeCnt, dist, s, t, std::numeric_limits<int>::max());
            maxFlow += newFlow;
        }
    }

    return maxFlow;
}

void addEdge(Graph::type& graph, int from, int to, int capacity) {
    Graph::Edge a {from, to, -1, 0, capacity, graph[to].adj.size()};
    Graph::Edge rev {to, from, -1, 0, 0, graph[from].adj.size()};
    graph[from].adj.push_back(a);
    graph[to].adj.push_back(rev);
}

} // namespace dinic

int solve(Graph::type& graph, int typesCount) {
    auto components = cycles::getComponents(std::move(graph));

    Graph::type bipart(components.size() + typesCount + 2);
    // std::vector<std::vector<int>> bipart(size, std::vector<int>(size, 0));
    auto bipart2 = [&components](int i) -> int {
        return i + components.size();
    };
    const int source = bipart.size() - 2;
    const int drain = bipart.size() - 1;

    for (int i = 0; i < components.size(); ++i) {
        std::unordered_map<int, int> typeCounter;
        for (int type : components[i]) {
            --type;
            ++typeCounter[type];
            // if (bipart[i][bipart2(type)] == 0) bipart[i][bipart2(type)] = 1;
            // else ++bipart[i][bipart2(type)];
        }
        for (auto x : typeCounter) {
            dinic::addEdge(bipart, i, bipart2(x.first), x.second);
        }
    }
    for (int i = 0; i < components.size(); ++i) {
        dinic::addEdge(bipart, source, i, (components[i].size() > 1) ? int(components[i].size() - 1) : 1);
        // bipart[source][i] = (components[i].size() > 1) ? (components[i].size() - 1) : 1;
    }
    for (int i = 0; i < typesCount; ++i) {
        dinic::addEdge(bipart, bipart2(i), drain, 1);
        // bipart[bipart2(i)][drain] = 1;
    }

    return dinic::maxFlow(bipart, source, drain);
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph::type graph(n);
    int typesCount = 0;

    for (int i = 0; i < m; ++i) {
        int u, v, s;
        std::cin >> u >> v >> s;
        --u;
        --v;
        typesCount = std::max(typesCount, s);
        graph[u].adj.push_back({u, v, s});
        graph[v].adj.push_back({v, u, s});
    }

    std::cout << solve(graph, typesCount);

    return 0;
}
