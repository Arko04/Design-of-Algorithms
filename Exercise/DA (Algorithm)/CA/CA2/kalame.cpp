#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int INF = 1000000;

int n, m, dp[MAXN][MAXN];
char s[MAXN], t[MAXN];

int compute_dp(int a, int b) {
    if (b == m) 
        return 0;
    if (dp[a][b] != -1) 
        return dp[a][b];

    int ret = INF;
    for (int i = 0; i < n; i++) {
        if (s[i] == s[a]) {
            for (int j = -1; j <= 1; j++) {
                if (!j || i + j < 0 || i + j >= n)
                    continue;
                if (s[i + j] != t[b])
                    continue;
                ret = min(ret, compute_dp(i + j, b + 1) + abs(i - a) + 1);
            }
        }
    }
    return dp[a][b] = ret;
}

int main() {
    memset(dp, -1, sizeof dp);

    cin >> n >> m >> s >> t;
    
    int sol = INF;

    for (int i = 0; i < n; i++) {
        if (s[i] == t[0]) {
            sol = min(sol, compute_dp(i, 1));
        }
    }
    
    if (sol >= INF) 
        cout << "-1\n";
    else
        cout << sol << '\n';
}
