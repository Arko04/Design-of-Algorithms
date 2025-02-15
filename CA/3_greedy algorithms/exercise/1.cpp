// https://chatgpt.com/share/67450d9a-c918-8009-9042-d020bc2e1cb2
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// // Function to compute the sum of adjacent elements
// vector<long long> adjacentSums(const vector<long long>& arr) {
//     vector<long long> result;
//     for (size_t i = 0; i < arr.size() - 1; i++) {
//         result.push_back(arr[i] + arr[i + 1]);
//     }
//     return result;
// }
// long long maxNonAdjacentSum(const vector<long long>& a) {
//     long long n = a.size();
//     if (n == 0) return 0; // No elements
//     if (n == 1) return a[0]; // Single element

//     // Initialize DP array
//     vector<long long> dp(n, 0);

//     // Base cases
//     dp[0] = a[0];
//     dp[1] = max(a[0], a[1]);

//     // Fill the DP table
//     for (long long i = 2; i < n; i++) {
//         dp[i] = max(dp[i-1], a[i] + dp[i-2]);
//     }

//     // Result is the last element in the DP table
//     return dp[n-1];
// }
// // Function to check if we can form at least `k` groups with `mid` actors per group
// bool isFeasible(long long mid, const vector<long long> &c, long long n, long long k, const vector<long long>& adjacent_sums)
// {
//     vector<long long> groups(n+);
//     vector<long long> only(n+1);
//     for (long long i = 0; i <= n; i++)
//     {
//         only[i] = c[i]/mid;
//         groups[i] = (adjacent_sums[i]) / mid; // Number of groups we can form with current age
//     }
//     return maxNonAdjacentSum(groups)>=k;
// }
bool isFeasible(long long mid, const vector<long long> &c, long long n, long long k, const vector<long long>& adjacent_sums)
{
    long long groups = 0;
    vector<long long> remainder;
    remainder.push_back(0);
    for (long long i = 0; i < n; i++)
    {
        long long now_groups = (remainder[i] + c[i]) / mid; // Number of groups we can form with current age
        remainder.push_back((remainder[i] + c[i]) / mid);
        groups += now_groups;
        if (groups >= k)
            return true; // Early exit if we already have enough groups
    }
    return groups >= k;
}

int main()
{
    long long t;
    cin >> t; // Number of test cases
    vector<long long> results;

    while (t--)
    {
        long long n, k;
        cin >> n >> k;

        vector<long long> c(n+2);
        c[0]= 0;
        for (long long i = 1; i <= n; i++)
        {
            cin >> c[i];
        }
        c[n+1] = 0;

        // Binary search for the maximum group size
        vector<long long> adjacent_sums = adjacentSums(c);
        long long low = 1, high = 2* max(adjacent_sums) max(adjacent_sums - max(adjacent_sums)), best = 0;
        while (low <= high)
        {
            long long mid = low + (high - low) / 2;
            if (isFeasible(mid, c, n, k, adjacent_sums))
            {
                best = mid;    // Update best result
                low = mid + 1; // Search for larger group sizes
            }
            else
            {
                high = mid - 1; // Search for smaller group sizes
            }
        }

        // `best` now holds the maximum mid such that `k` groups can be formed
        results.push_back(best * k);
    }

    // Output all results
    for (long long result : results)
    {
        cout << result << endl;
    }

    return 0;
}


