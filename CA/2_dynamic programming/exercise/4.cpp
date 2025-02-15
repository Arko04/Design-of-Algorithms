// https://chatgpt.com/share/672f4a00-6518-8003-86a5-ebe29163cf6b
// https://leetcode.com/problems/burst-balloons/solutions/5769317/easy-solution-using-matrix-chain-multiplication/
// https://leetcode.com/problems/burst-balloons/solutions/892552/for-those-who-are-not-able-to-understand-any-solution-with-diagram/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long

int main()
{
    ll n;
    cin >> n;
    ll a[n + 2];
    a[0] = 1;
    a[n + 1] = 1;
    bool b[n+2][n+2];
    for (int i = 0 ; i < n+2; i++)
    {
        for (int j = 0; j < n+2; j++)
        {
            b[i][j] = false;
        }
    }
    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    ll dp[n + 2][n + 2];
    for (ll j = 0; j <= n; j++)
    {
        for (ll i = j + 1; i <= n + 1; i++)
        {
            dp[i][j] = 0;
            b[i][j] = true;
        }
    }
    for (ll i = 1; i <= n; i++)
    {
        dp[i][i] = a[i - 1] * a[i] * a[i + 1];
        b[i][i] = true;
    }
    for (ll i = 1; i <= n - 1; i++)
    {
        dp[i][i + 1] = max(a[i - 1] * a[i] * a[i + 1] + a[i - 1] * a[i + 1] * a[i + 2],
                           a[i] * a[i + 1] * a[i + 2] + a[i - 1] * a[i] * a[i + 2]);
        b[i][i+1] = true;
    }

    for (ll right = 1; right <= n; right++)
    {
        for (ll left = right - 2; left >= 1; left--)
        {
            if (b[left][right] == true)
            {
                continue;
            }
            ll maximum = 0;
            for (ll k = left; k <= right; k++)
            {
                ll temp = a[left - 1] * a[k] * a[right + 1] + dp[left][k - 1] + dp[k + 1][right];
                maximum = max(temp, maximum);
            }
            dp[left][right] = maximum;
            b[left][right] = true;
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}