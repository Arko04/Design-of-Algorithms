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

void solver(std::vector<int>& vec,
            std::vector<int>::iterator first,
            std::vector<int>::iterator last,
            int currLevel,
            int k) {
    if (first >= last) return;
    auto m = alg::max_element(first, last);
    if (currLevel > k) *m = 0;
    solver(vec, m + 1, last, currLevel + 1, k);
    solver(vec, first, m, currLevel + 1, k);
}

void solve(std::vector<int>& vec, int k) {
    solver(vec, vec.begin(), vec.end(), 0, k);
}

int main() {
    int t;
    std::cin >> t;

    for (int test = 0; test < t; ++test) {
        int n, k;
        std::cin >> n >> k;
        std::vector<int> vec(n);
        for (int i = 0; i < n; ++i) {
            int num;
            std::cin >> num;
            vec[i] = num;
        }

        solve(vec, k);
        for (int num : vec) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
