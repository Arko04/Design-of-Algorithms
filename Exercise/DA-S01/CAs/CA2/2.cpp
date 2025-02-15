#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

ll solve(int n, int h) {
    // The count of all BSTs with nodes=n and max_height=h:
    // Ans(n, h) = sigma<1, n>[Ans(i-1, h-1) * Ans(n-1, h-1)]
    // (If the i-th largest number is the root,
    //  the left subtree contains i-1 nodes and
    //  the right subtree contains n-i nodes)

    std::vector<std::vector<ll>> dp(n + 1, std::vector<ll>(n + 1, 0LL));
    std::fill(dp[0].begin(), dp[0].end(), 1LL);

    for (int i = 1; i < dp.size(); ++i) {     // nodes
        for (int j = 1; j < dp.size(); ++j) { // max height

            for (int k = 0; k < i; ++k) { // sigma
                dp[i][j] += dp[k][j - 1] * dp[i - k - 1][j - 1];
            }

        }
    }

    // The count of all BSTs with nodes=n is Ans(n, n)
    // The count of all BSTs with nodes=n and max_height=h is Ans(n, h)
    // We want all BSTs that have min_height=h
    // So we want: Ans(n, n) - Ans(n, h)
    return dp.back()[n] - dp.back()[h - 1];
}

int main() {
    int n, h;
    std::cin >> n >> h;
    std::cout << solve(n, h);
    return 0;
}
