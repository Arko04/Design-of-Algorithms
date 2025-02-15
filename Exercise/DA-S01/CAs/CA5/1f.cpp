#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>

template <class T>
class Array2D {
public:
    // clang-format off
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    // clang-format on

    Array2D(size_type row, size_type col)
        : arr_(new value_type[row * col]()),
          row_(row),
          col_(col) {}

    explicit Array2D(size_type n)
        : Array2D(n, n) {}

    ~Array2D() {
        delete[] arr_;
    }

    Array2D(const Array2D& other)
        : Array2D(other.row_, other.col_) {
        std::copy(other.arr_, other.arr_ + other.size(), arr_);
    }
    Array2D(Array2D&& other) noexcept {
        swap(*this, other);
    }

    Array2D& operator=(const Array2D& rhs) {
        Array2D temp(rhs);
        swap(*this, temp);
        return *this;
    }
    Array2D& operator=(Array2D&& rhs) noexcept {
        swap(*this, rhs);
        return *this;
    }

    friend void swap(Array2D& a, Array2D& b) noexcept {
        using std::swap;
        swap(a.arr_, b.arr_);
        swap(a.row_, b.row_);
        swap(a.col_, b.col_);
    }

    void fill(const_reference x) {
        std::fill(arr_, arr_ + size(), x);
    }

    size_type rows() const noexcept { return row_; }
    size_type cols() const noexcept { return col_; }
    size_type size() const noexcept { return row_ * col_; }

    // clang-format off
    pointer       operator[](size_type i)       noexcept { return arr_ + i * col_; }
    const_pointer operator[](size_type i) const noexcept { return arr_ + i * col_; }
    // clang-format on

private:
    pointer arr_ = nullptr;
    size_type row_;
    size_type col_;
};

struct Loc {
    int x;
    int y;
};

struct Tile {
    char main;
    char cheese;
};

namespace Types {
constexpr char Wall = 'Y';
constexpr char Cat = 'Z';
} // namespace Types

constexpr int DIRECTIONS = 4;
const Loc offset[DIRECTIONS] {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

template <class T>
bool isValidBoundary(const Array2D<T>& arr, int row, int col) {
    if (col < 0 || row < 0) return false;
    if (col >= arr.cols() || row >= arr.rows()) return false;
    return true;
}

std::vector<int> BFS_getPath(const Array2D<int>& graph, int s, int t, bool& result) {
    std::vector<int> parent(graph.rows(), -1);
    std::vector<bool> visited(graph.rows(), false);

    std::queue<int> queue;
    visited[s] = true;
    queue.push(s);

    while (!queue.empty()) {
        const auto curr = queue.front();
        queue.pop();

        for (int i = 0; i < graph.rows(); ++i) {
            if (!visited[i] && graph[curr][i] > 0) {
                if (i == t) {
                    parent[i] = curr;
                    result = true;
                    return parent;
                }

                visited[i] = true;
                queue.push(i);
                parent[i] = curr;
            }
        }
    }

    result = false;
    return parent;
}

Array2D<int> BFS_calcDist(const Array2D<Tile>& arr, Loc startPos) {
    Array2D<int> dist(arr.rows(), arr.cols());
    dist.fill(std::numeric_limits<int>::max());

    Array2D<bool> visited(arr.rows(), arr.cols());
    visited.fill(false);
    std::queue<Loc> queue;

    visited[startPos.x][startPos.y] = true;
    queue.push({startPos.x, startPos.y});

    dist[startPos.x][startPos.y] = 0;
    int length = 1;
    int prevLayerElems = 1;
    int currLayerElems = 0;

    while (!queue.empty()) {
        const auto curr = queue.front();
        queue.pop();

        for (int i = 0; i < DIRECTIONS; ++i) {
            const auto r = curr.x + offset[i].x;
            const auto c = curr.y + offset[i].y;

            if (!isValidBoundary(arr, r, c)) continue;
            if (visited[r][c]) continue;
            if (arr[r][c].main == Types::Wall) continue;

            visited[r][c] = true;
            queue.push({r, c});
            dist[r][c] = length;
            ++currLayerElems;
        }

        if (--prevLayerElems == 0) {
            prevLayerElems = currLayerElems;
            currLayerElems = 0;
            ++length;
        }
    }

    return dist;
}

int edmondsKarp(Array2D<int> graph, int s, int t) {
    int maxFlow = 0;

    while (true) {
        bool pathRes;
        auto parent = BFS_getPath(graph, s, t, pathRes);
        if (!pathRes) break;

        int bottleneck = std::numeric_limits<int>::max();
        int v = t;
        while (v != s) {
            int u = parent[v];
            bottleneck = std::min(bottleneck, graph[u][v]);
            v = u;
        }

        v = t;
        while (v != s) {
            int u = parent[v];
            graph[v][u] += bottleneck;
            graph[u][v] -= bottleneck;
            v = u;
        }

        maxFlow += bottleneck;
    }

    return maxFlow;
}

int solve(Array2D<Tile>& mtx,
          Loc catPos,
          int miceCount,
          const std::vector<Loc>& cheesez,
          int cheeseCount,
          int timeLimit) {
    Array2D<int> graph(miceCount + cheeseCount + 2);
    const int source = miceCount + cheeseCount;
    const int drain = miceCount + cheeseCount + 1;
    auto bipart2 = [miceCount](int i) {
        return miceCount + i;
    };

    const auto distCat = BFS_calcDist(mtx, catPos);

    int miceCounter = 0;
    for (int i = 0; i < mtx.rows(); ++i) {
        for (int j = 0; j < mtx.cols(); ++j) {
            if (std::isdigit(mtx[i][j].main) && mtx[i][j].main != '0') {
                const auto distMouse = BFS_calcDist(mtx, {i, j});
                int cheeseCounter = 0;
                for (auto cheese : cheesez) {
                    if (distMouse[cheese.x][cheese.y] > timeLimit) {}
                    else if (distMouse[cheese.x][cheese.y] < distCat[cheese.x][cheese.y]) {
                        for (int i = 0; i < mtx[cheese.x][cheese.y].cheese - '0'; ++i) {
                            graph[miceCounter][bipart2(cheeseCounter + i)] = 1;
                        }
                    }
                    else if (distMouse[cheese.x][cheese.y] == distCat[cheese.x][cheese.y]) {
                        for (int i = 0; i < DIRECTIONS; ++i) {
                            auto x = cheese.x + offset[i].x;
                            auto y = cheese.y + offset[i].y;
                            if (!isValidBoundary(mtx, x, y)) continue;
                            if (distMouse[x][y] < distCat[x][y]) {
                                for (int i = 0; i < mtx[cheese.x][cheese.y].cheese - '0'; ++i) {
                                    graph[miceCounter][bipart2(cheeseCounter + i)] = 1;
                                }
                                break;
                            }
                        }
                    }
                    cheeseCounter += mtx[cheese.x][cheese.y].cheese - '0';
                }
                --mtx[i][j].main;
                int lastOne = miceCounter;
                ++miceCounter;
                while (mtx[i][j].main != '0') {
                    for (int i = 0; i < graph.cols(); ++i) {
                        graph[miceCounter][i] = graph[lastOne][i];
                    }
                    ++miceCounter;
                    --mtx[i][j].main;
                }
            }
        }
    }

    for (int i = 0; i < miceCount; ++i) {
        graph[source][i] = 1;
    }
    for (int i = 0; i < cheeseCount; ++i) {
        graph[bipart2(i)][drain] = 1;
    }

    for (int i = 0; i < graph.rows(); ++i) {
        for (int j = 0; j < graph.cols(); ++j) {
            std::cout << graph[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return edmondsKarp(graph, source, drain);
}

int main() {
    int n, t;
    std::cin >> n >> t;
    Array2D<Tile> mtx(n);
    std::vector<Loc> cheesez;
    cheesez.reserve(n);
    int miceCount = 0;
    int cheeseCount = 0;

    Loc catPos;

    for (int i = 0; i < mtx.rows(); ++i) {
        std::cin.get();
        for (int j = 0; j < mtx.cols(); ++j) {
            const char c = std::cin.get();
            if (std::isdigit(c) && c != '0') {
                miceCount += c - '0';
            }
            else if (c == Types::Cat) {
                catPos.x = i;
                catPos.y = j;
            }
            mtx[i][j] = Tile {c, 'X'};
        }
    }
    std::cin.get();
    for (int i = 0; i < mtx.rows(); ++i) {
        std::cin.get();
        for (int j = 0; j < mtx.cols(); ++j) {
            const char c = std::cin.get();
            if (std::isdigit(c) && c != '0') {
                cheeseCount += c - '0';
                cheesez.push_back({i, j});
                mtx[i][j].cheese = c;
            }
        }
    }

    std::cout << solve(mtx, catPos, miceCount, cheesez, cheeseCount, t);
    return 0;
}
