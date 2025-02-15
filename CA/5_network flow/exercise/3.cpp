#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <numeric>
using namespace std;

const double EPS = 1e-9;
const int INF = 1e9;

struct Edge {
    int to, rev;
    int cap, flow;
};

class Dinic {
public:
    vector<vector<Edge>> adj;
    vector<int> level, ptr;
    int n, s, t;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void addEdge(int u, int v, int cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap, 0});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (level[e.to] == -1 && e.flow < e.cap) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int pushed) {
        if (u == t) return pushed;
        for (int &i = ptr[u]; i < adj[u].size(); ++i) {
            Edge &e = adj[u][i];
            if (level[e.to] != level[u] + 1 || e.flow >= e.cap) continue;
            int tr = dfs(e.to, min(pushed, e.cap - e.flow));
            if (tr > 0) {
                e.flow += tr;
                adj[e.to][e.rev].flow -= tr;
                return tr;
            }
        }
        return 0;
    }

    int maxFlow() {
        int flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<double>> table(n, vector<double>(m));
        vector<vector<int>> result(n, vector<int>(m));
        vector<int> rowSum(n, 0), colSum(m, 0);
        int totalDemand = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> table[i][j];
                int floorVal = floor(table[i][j]);
                int ceilVal = ceil(table[i][j]);
                result[i][j] = floorVal;
                rowSum[i] += floorVal;
                colSum[j] += floorVal;
                totalDemand += floorVal;
            }
        }

        int source = n + m, sink = n + m + 1;
        Dinic dinic(n + m + 2, source, sink);

        for (int i = 0; i < n; ++i) {
            int demand = accumulate(table[i].begin(), table[i].end(), 0.0) - rowSum[i];
            dinic.addEdge(source, i, demand);
        }

        for (int j = 0; j < m; ++j) {
            int demand = 0;
            for (int i = 0; i < n; ++i) {
                demand += table[i][j] - result[i][j];
            }
            dinic.addEdge(n + j, sink, demand);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dinic.addEdge(i, n + j, 1);
            }
        }

        if (dinic.maxFlow() == totalDemand) {
            cout << "YES\n";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    cout << result[i][j] << " ";
                }
                cout << "\n";
            }
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
