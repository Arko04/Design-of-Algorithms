#include <iostream>
#include <vector>

long long solve(int s, const std::vector<int>& p) {
    struct Interval {
        Interval() = default;
        Interval(int first_, int last_, int i_)
            : first(first_),
              last(last_),
              i(i_) {}
        int first, last, i;
    };
    std::vector<Interval> intvls;

    for (int i = 0; i < p.size(); ++i) {
        int right, left;

        for (right = i + 1; right < p.size(); ++right) {
            if (p[right] % p[i] != 0) {
                --right;
                break;
            }
        }
        for (left = i - 1; left >= 0; --left) {
            if (p[left] % p[i] != 0) {
                ++left;
                break;
            }
        }

        if (right == p.size()) right = p.size() - 1;
        if (left == -1) left = 0;

        if (left != right) {
            intvls.emplace_back(left, right, i);
            i = right;

            for (int k = intvls.size() - 2; k >= 0; --k) {
                if (intvls[k].first >= intvls.back().first &&
                    intvls.back().last >= intvls[k].last) {
                    intvls.erase(intvls.begin() + k);
                }
            }
        }
    }

    long long result = (p.size() - 1) * s;
    for (const auto x : intvls) {
        if (p[x.i] < s) {
            result += (p[x.i] - s) * (x.last - x.first);
        }
    }

    return result;
}

int main() {
    int t;
    std::cin >> t;
    for (int test = 0; test < t; ++test) {
        int n, s;
        std::cin >> n >> s;
        std::vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> p[i];
        }
        std::cout << solve(s, p) << '\n';
    }
    return 0;
}
