#include <bits/stdc++.h>
using namespace std;
#define int long long

int const N = 505, INF = 1ll*1e9*1e9;
int n, m, k, ans = INF;
int a[N][N], ps[N][N];


int get_sum(int x1, int y1, int x2, int y2) {
    return ps[x2][y2] - ps[x2][y1] - ps[x1][y2] + ps[x1][y1];
}


int32_t main() {
    ios::sync_with_stdio(false), cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            ps[i+1][j+1] = ps[i][j+1] + ps[i+1][j] - ps[i][j] + a[i][j];
        }
    }

    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < m; y1++) {
            for (int x2 = x1+1; x2 <= n; x2++) {
                int length = ceil(1.0 * k / (x2 - x1));
                int y2 = y1 + length;
                if (y2 <= m) {
                    ans = min(ans, get_sum(x1, y1, x2, y2));
                }
            }
        }
    }

    cout << ans << '\n';

}