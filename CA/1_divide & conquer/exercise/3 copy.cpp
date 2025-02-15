#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long int
ll binary_search_left(const vector<ll>& v, ll left, ll right, const ll& target)
{
    ll median = (left + right) / 2;
    if (target < v[median])
    {
        binary_search_left(v, left, median-1, target);
    }
    else(target > v[median])
    {
        binary_search_left(v, median + 1, right, target);
    }
}
int main()
{
    int n , k , A, B;
    cin >> n >> k >> A >> B;
    vector<ll> people(k);
    for (int i  = 0; i < k; i++)
    {
        cin >> people[i];
    }
    sort(people.begin(), people.end());
    for (int i  = 0; i < k; i++)
    {
        cout << people[i];
    }
    ll left = 0;
    ll right = people.size() - 1;

    ll target_left, target_right;
    
    auto first_occurrence = lower_bound(people.begin(), people.end(), target_left);
    auto last_occurrence = upper_bound(people.begin(), people.end(), target_right);
    
}
