#include <iostream>
#include <vector>
using namespace std;
#define ll long long int
const ll size = 1e3 + 1;
ll r = 1e9 + 7;

ll factorial(ll n) {
    ll result = 1;
    for (ll i = 1; i <= n; i++) {
        result  = (result * i) % r;
    }
    return result%r;
}

ll choose(ll p, ll q) {
    return (factorial(p + q) / (factorial(p) * factorial(q))) % r;
}
ll calc(vector<ll>& a) {
    vector<ll> right, left;
    ll init = a[0];
    ll n = a.size();

    for (ll i = 1; i < n; i++) {
        if (a[i] > init) {
            right.push_back(a[i]);
        } else if (a[i] < init){
            left.push_back(a[i]);
        }
    }

    ll size_r = right.size();
    ll size_l = left.size();

    if (size_r == 0 && size_l == 0)
    {
        return 1;
    }
    else if (size_r == 0)
    {
        return calc(left) % r;
    }
    else if (size_l == 0)
    {
        return calc(right) % r;
    }
    
    return (choose(size_r, size_l)%r * calc(right)%r * calc(left)%r) % r;
}

int main() {
    ll n;
    cin >> n;

    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll s = calc(a);
    if (s  == 0)
    cout << r - 1 << endl;
    else
    cout << s - 1 << endl;

    return 0;
}
