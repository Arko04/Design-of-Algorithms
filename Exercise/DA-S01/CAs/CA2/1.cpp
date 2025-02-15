#include <iostream>
#include <limits>
#include <type_traits>
#include <vector>

template <class T>
inline T min(T&& a) { return std::forward<T>(a); }
template <class T1, class T2, class... Args>
inline typename std::common_type<T1, T2, Args...>::type
min(T1&& a, T2&& b, Args&&... args) {
    return (b < a) ? min(std::forward<T2>(b), std::forward<Args>(args)...) :
                     min(std::forward<T1>(a), std::forward<Args>(args)...);
}

using ll = long long;

struct Input {
    int height;
    int cost;
};

ll solve(const std::vector<Input>& inp) {
    // For each wall, only the two next to it matter.
    // And for each wall and the one before it,
    // there are 9 permutations to be considered for increasing the height:

    // . .   . .   | .   . .   . .   | .   . |   . |   | |
    // . .   | .   | .   . |   | |   | |   . |   | |   | |

    // As we move forward, we will choose the permutation that will have the least cost.

    std::vector<std::vector<ll>> dp(inp.size(),
                                    std::vector<ll>(3, std::numeric_limits<ll>::max()));
    dp[0][0] = 0;
    dp[0][1] = inp[0].cost;
    dp[0][2] = inp[0].cost * 2;

    for (int i = 1; i < inp.size(); ++i) {
        for (int j = 0; j < 3; ++j) {

            for (int k = 0; k < 3; ++k) {
                if (inp[i].height + j == inp[i - 1].height + k) continue;
                dp[i][j] = min(dp[i][j], dp[i - 1][k]);
            }
            dp[i][j] += inp[i].cost * j;

        }
    }

    return min(dp.back()[0], dp.back()[1], dp.back()[2]);
}

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;
        std::vector<Input> inp;
        inp.reserve(n);

        for (int k = 0; k < n; ++k) {
            int h, c;
            std::cin >> h >> c;
            inp.push_back({h, c});
        }

        std::cout << solve(inp) << '\n';
    }

    return 0;
}
