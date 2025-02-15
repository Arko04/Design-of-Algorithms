#include <algorithm>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>

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
        swap(a.size_, b.size_);
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

template <class T,
          class = typename std::enable_if<std::is_integral<T>::value>::type>
struct BitFlag {
    static bool test(T num, std::size_t pos) {
        return num & (static_cast<T>(1) << pos);
    }

    static T set(T num, std::size_t pos) {
        return num | (static_cast<T>(1) << pos);
    }

    static T reset(T num, std::size_t pos) {
        return num & ~(static_cast<T>(1) << pos);
    }

    static T set(T num, std::size_t pos, bool val) {
        return val ? set(num, pos) : reset(num, pos);
    }

    static T flip(T num) {
        return ~num;
    }

    static T flip(T num, std::size_t pos) {
        return num ^ (static_cast<T>(1) << pos);
    }

    static std::size_t count(T num) {
        std::size_t count = 0;
        while (num) {
            if (num & 1) ++count;
            num >>= 1;
        }
        return count;
    }

    static std::size_t highestSet(T num) {
        if (!num) return 0;
        std::size_t count = 1;
        while (num >>= 1) ++count;
        return count;
    }
};

using ll = long long;

int solve(Array2D<bool>& graph, int leafCount) {
    const int n = graph.rows();
    const int nPow2 = 1 << n;

    // dp's rows are subgraphs (each bit representing a node)
    // dp's cols are the leaves (each set bit means that it's a leaf)
    // each cell in dp shows how many graphs with row set nodes exist that have the col set leaves.
    std::vector<std::vector<int>> dp(nPow2,
                                     std::vector<int>(nPow2, 0LL));

    // when there are 2 nodes, both of them are leaves.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) { // graph is undirected.
            if (!graph[i][j]) continue;
            const int masked = (1 << i) | (1 << j);
            dp[masked][masked] = 1; // there is one graph with 2 nodes and 2 leaves.
        }
    }

    using Mask = BitFlag<int>;

    // fill dp row major (i, j)
    for (int i = 0; i < nPow2; ++i) {
        if (Mask::count(i) < 3) continue; // graphs with 2 nodes have been handled above.
        for (int j = 0; j < nPow2; ++j) {
            if ((i | j) != i) continue; // 'j' is not a subgraph of 'i' (cannot be its leaves)

            for (int a = 0; a < n; ++a) {
                if (!Mask::test(j, a)) continue; // 'a' has to be a node of 'j' (node of i's leaves)
                for (int b = 0; b < n; ++b) {
                    if (Mask::test(i, b) &&  // 'b' is the node of our subgraph 'i',
                        !Mask::test(j, b) && // which is not a leaf,
                        graph[b][a]) {       // and is connected to 'a' in the main graph.
                        // to get the possible ways for (i, j),
                        // we remove the 'a' node (which was a leaf) from the 'i' subgraph,
                        // so the total count of this new subgraph can be used because we can
                        // connect any of the non-leaf nodes to the removed 'a'
                        const int graphNoA = Mask::reset(i, a);
                        const int leavesNoA = Mask::reset(j, a);
                        dp[i][j] += dp[graphNoA][leavesNoA];
                        // and if we connect to a leaf node, then the 'a' node will replace that leaf.
                        // so there is a case where when we remove 'a', 'b' will become a leaf and we connect to that.
                        dp[i][j] += dp[graphNoA][Mask::set(leavesNoA, b)];
                    }
                }
            }

            // divide by the number of leaves.
            auto x = Mask::count(j);
            if (x) dp[i][j] /= x;
        }
    }

    // count nodes=n with leaves=leafCount
    int res = 0;
    for (int j = 0; j < nPow2; ++j) {
        // dp.back() is dp[binary111111...] which means all n nodes.
        // add up all cells in which leaves=leafCount
        if (Mask::count(j) == leafCount) res += dp.back()[j];
    }
    return res;
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    Array2D<bool> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        graph[u][v] = true;
        graph[v][u] = true;
    }
    std::cout << solve(graph, k);
    return 0;
}
