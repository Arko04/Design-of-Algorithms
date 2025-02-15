#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long int
ll residual = 1e8;
int main()
{
    ll n, m, v, c;
    cin >> n >> m >> v >> c;
    ll dp[n+1][m+1][2];

    dp[0][0][0] = 1;
    dp[0][0][1] = 1;   
    for (ll i = 0; i <= n; i++)
    {
        for (ll j = 0; j <= m; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            ll ans1 = 0;
            for (ll k = i-1; k >= max(i - v, 0LL);k--)
            {
                ans1 += dp[k][j][1];
            }
            dp[i][j][0]  = ans1 % residual;
            
            ll ans2 = 0;
            for (ll k = j-1; k >= max(j - c, 0LL);k--)
            {
                ans2 += dp[i][k][0];
            }
            dp[i][j][1] = ans2 % residual;
        }
    }
    cout << (dp[n][m][0] + dp[n][m][1]) % residual;
}
