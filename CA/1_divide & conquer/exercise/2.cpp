#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#define ll long long int

void merge(vector <ll>& sum, ll left,ll mid,ll right)
{
    vector<ll> new_interval;
    ll start = left;
    ll inter = mid + 1; 
    ll end = right;
    while (start <= mid or inter <= end)
    {
        if(start > mid)
        {
            new_interval.push_back(sum[inter]);
            inter += 1;
        }
        else if(inter > end)
        {
            new_interval.push_back(sum[start]);
            start += 1;
        }
        else if (sum[start] <= sum[inter])
        {
            new_interval.push_back(sum[start]);
            start += 1;
        }
        else if(sum[start] > sum[inter]){
            new_interval.push_back(sum[inter]);
            inter += 1;
        }
    }
    for(ll i = left, j = 0;i<=right;i++, j++)
    {
        sum[i] = new_interval[j];
    }
}

ll counter(const vector<ll>& sum, ll left,ll mid,ll right,ll lower,ll upper)
{
    ll start = left;
    ll inter = mid+1;
    ll end = right;
    ll j = inter;
    ll all = (mid - left + 1)*(right - mid);
    ll count = 0;
    for (ll i = left; i <= mid; i++)
    {
        while (sum[j] - sum[i] < lower && j <= end)
        {
            j += 1;
        }

        count += j - inter;
    }
    // cout << count <<endl;
    j = end;
    for (ll i = mid; i >= left; i--)
    {
        while (sum[j] - sum[i] > upper && j >= mid+1)
        {
            j -= 1;
        }

        count += end - j;
    }
    // cout << "all :"<< all <<endl;
    // cout << "count: "<< count << endl;
    // cout << count<<endl;
    return all - count;

}
ll calc(vector<ll>& sum, ll left, ll right, ll lower, ll upper)
{
    if (left == right)
    {
        return (sum[right]) <= upper && (sum[right]) >= lower;
    }
    ll mid = (left + right) / 2;
    ll count_l = calc(sum, left, mid, lower, upper);
    ll count_r = calc(sum, mid + 1, right, lower, upper);
    ll count_both = counter(sum, left, mid, right, lower, upper);
    merge(sum, left, mid, right);
    return count_l + count_r + count_both;

}
int main()
{
    string line;
    getline(cin, line);  // Take the whole line as input

    stringstream ss(line);  // Create a stringstream object
    ll number;
    vector<ll> numbers;

    while (ss >> number) {  // Extract numbers separated by spaces
        numbers.push_back(number);  // Add each number to the vector
    }

    ll lower, upper;
    cin >> lower >> upper;

    // for (int i = 0; i < numbers.size(); i++)
    // {
    //     cout << numbers[i] << ' ';
    // }
    // cout << '\n' << l << ' ' << u;

    vector<ll> sum;
    sum.push_back(numbers[0]);
    for (ll i = 1; i < numbers.size(); i++)
    {
        sum.push_back(sum[i-1] + numbers[i]);
    }
    // cout << "the ans:" << calc(sum, 0, sum.size() - 1, lower, upper)<<endl;
    // for (int i = 0; i < sum.size(); i++)
    // {
    //     cout << sum[i] << ' ';
    // }
    cout <<calc(sum, 0, sum.size() - 1, lower, upper)<<endl;
}