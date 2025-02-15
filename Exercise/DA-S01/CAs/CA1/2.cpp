#include <iostream>
#include <vector>

namespace alg {

template <class Iter, class Compare>
Iter max_element(Iter first, Iter last, Compare comp) {
    if (first == last) return last;
    Iter max(first);
    for (++first; first != last; ++first) {
        if (comp(*max, *first)) max = first;
    }
    return max;
}

template <class Iter>
Iter max_element(Iter first, Iter last) {
    return max_element(first, last, std::less {});
}

} // namespace alg

template <class T>
struct BitFlag {
    static bool test(T i, std::size_t pos) {
        return i & (static_cast<T>(1) << pos);
    }

    static T set(T i, std::size_t pos) {
        return i | (static_cast<T>(1) << pos);
    }

    static T reset(T i, std::size_t pos) {
        return i & ~(static_cast<T>(1) << pos);
    }

    static T set(T i, std::size_t pos, bool val) {
        if (val) return set(i, pos);
        else return reset(i, pos);
    }

    static T flip(T i) {
        return ~i;
    }

    static T flip(T i, std::size_t pos) {
        return i ^ (static_cast<T>(1) << pos);
    }

    static std::size_t highestSetBit(T i) {
        if (!i) return 0;
        std::size_t count = 1;
        while (i >>= 1) ++count;
        return count;
    }
};

int solve(const std::vector<int>& inp, int bitPos = 30) {
    if (bitPos < 0) return 0;

    std::vector<int> bitIs1;
    std::vector<int> bitIs0;

    for (int i : inp) {
        if (BitFlag<int>::test(i, bitPos)) bitIs1.push_back(i);
        else bitIs0.push_back(i);
    }

    if (bitIs1.empty()) return solve(bitIs0, bitPos - 1);
    if (bitIs0.empty()) return solve(bitIs1, bitPos - 1);
    return std::min(solve(bitIs1, bitPos - 1), solve(bitIs0, bitPos - 1))
           + (1 << bitPos);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> inp(n);
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        inp[i] = t;
    }

    int high = BitFlag<int>::highestSetBit(*alg::max_element(inp.begin(), inp.end()));

    std::cout << solve(inp, high);
    return 0;
}
