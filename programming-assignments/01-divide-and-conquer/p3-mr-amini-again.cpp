// https://chatgpt.com/share/670fbf2b-c9f0-8003-b255-69df4be8d24c
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
using namespace std;
#define ll long long int
ll lower_bound(vector<ll> & v, ll left, ll right, ll target_left)
{
    if (left >= right)
    {
        return left;
    }
    ll median = (left + right)/2;
    
    if (target_left < v[median])
    {
        return lower_bound(v, left, median,  target_left);
    }
    else if (target_left == v[median])
    {
        ll res = lower_bound(v, left, median,  target_left);
        if (target_left == v[res])
        {
            return res;
        }
        else
        {
            return median;
        }
    }
    else
    {
        return lower_bound(v, median+1, right,  target_left);
    }
}
ll upper_bound(vector<ll> & v, ll left, ll right, ll target_right)
{
    if (left >= right)
    {
        return right;
    }
    ll median = (left + right)/2;
    
    if (target_right < v[median])
    {
        return upper_bound(v, left, median,  target_right);
    }
    else if (target_right == v[median])
    {
        ll res = upper_bound(v, median + 1, right,  target_right);
        if (target_right == v[res])
        {
            return res;
        }
        else
        {
            return median;
        }
    }
    else
    {
        return upper_bound(v, median+1, right,  target_right);
    }
}
ll count(vector<ll> &v, ll target_left, ll target_right, ll A, ll B)
{
    ll left = 0;
    ll right = v.size()-1;
    ll first_occurrence = lower_bound(v, left , right, target_left);
    ll last_occurrence = upper_bound(v, left , right, target_right);
    ll counter, count_left, count_right;
    ll res;
    ll length = target_right - (target_left - 1);
    ll mid = target_right - (length/2);
    // cout << target_left << ' ' << mid << ' ' << target_right << endl;
    if (first_occurrence == last_occurrence && first_occurrence < v.size() && !(v[last_occurrence] <= target_right && v[first_occurrence] >= target_left) )
    {
        // cout << "no" << endl;
        return A;
    }
    if (target_left >= target_right)
    {
        counter = (last_occurrence - first_occurrence + 1);
        res = length * counter * B;
        // cout << "nothing" <<endl;
        return res;
    }
    /////??????????????????????????????????????????????

    if (v[first_occurrence] < target_left)
    {
        first_occurrence +=1;
    }
    if(v[last_occurrence] >target_right)
    {
        last_occurrence-=1;
    }
    counter = (last_occurrence - first_occurrence + 1);
    res = length * counter * B;
    if (res == 0)
    {
        res = +1000000;
    }

    
    
    count_left = count(v, target_left, mid, A, B);
    count_right = count(v, mid + 1, target_right, A, B);


    // cout << "first occurance: " << first_occurrence << ' ' << "last ocuurance: " << last_occurrence<<endl;
    // cout << "counter: "<<counter << "length: " << length<< endl;
    // cout << "res: " << res <<  ' ' << count_left << '+' << count_right<<endl;
    return min(res, count_left + count_right);
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
    // for (int i  = 0; i < k; i++)
    // {
    //     cout << people[i] << ' ';
    // }
    // cout << endl;
    ll left = 0;
    ll right = people.size() - 1;
    ll station_no = pow(2, n);
    // ll target_left =  2, target_right = 8 ;
    ll target_left =  1, target_right = station_no ;
    ll ans = count(people, target_left ,target_right, A, B);
    // cout << '\n' << ans << endl;
    cout << ans << endl;
}
