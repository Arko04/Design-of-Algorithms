#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#define ll long long int
const ll INF = 1e9 + 1;

int main()
{
    ll n;
    cin >> n;
    ll f[2][n+1];
    bool b[2][n+1];
    vector<ll> a;
    vector<string> s1;
    vector<string> s2;
    for (ll i = 1; i <= n; i++)
    {
        ll x;
        cin >> x;
        a.push_back(x);
    }
    for (ll i = 1; i <= n;i++)
    {
        string y1, y2;
        cin >> y1;
        s1.push_back(y1);

        y2 = y1;
        reverse(y2.begin(), y2.end());
        s2.push_back(y2);
    }
    // start from index 0
    f[0][0] = 0;
    b[0][0] = true;
    f[1][0] = a[0];
    b[1][0] = true;

    for(ll i = 1; i < n; i++)
    {
        if (b[0][i-1] == false && b[1][i-1] == false)
        {
            cout << -1;
            return 0;
        }
        f[0][i] = INF;
        if (s1[i-1] <= s1[i] && s2[i-1] <= s1[i] && b[0][i-1] == true && b[1][i-1] == true)
        {
            f[0][i] = min(f[0][i-1], f[1][i-1]);
            b[0][i] = true;
        }
        else if (s1[i-1] <= s1[i] && b[0][i-1] == true)
        {
            f[0][i] = f[0][i-1];
            b[0][i] = true;
        }
        else if (s2[i-1] <= s1[i] && b[1][i-1] == true)
        {
            f[0][i] = f[1][i-1];
            b[0][i] = true;
        }
        else
        {
            b[0][i] = false;
        } 

        f[1][i] = INF;
        if (s1[i-1] <= s2[i] && s2[i-1] <= s2[i] && b[0][i-1] == true && b[1][i-1] == true)
        {
            f[1][i] = min(f[0][i-1], f[1][i-1]) + a[i];
            b[1][i] = true;
        }
        else if (s1[i-1] <= s2[i] && b[0][i-1] == true)
        {
            f[1][i] = f[0][i-1] + a[i];
            b[1][i] = true;
        }
        else if (s2[i-1] <= s2[i] && b[1][i-1] == true)
        {
            f[1][i] = f[1][i-1] + a[i];
            b[1][i] = true;
        }
        else
        {
            b[1][i] = false;
        }      
    } 
    ll ans;
    if (b[0][n-1] == true && b[1][n-1] == true)
    {
        ans = min(f[0][n-1], f[1][n-1]);
    }
    else if (b[0][n-1] == true)
    {
        ans = f[0][n-1];
    }
    else if (b[1][n-1] == true)
    {
        ans = f[1][n-1];
    }
    else
    {
        ans = -1;
    }
    cout << ans;
}