// https://chatgpt.com/share/67450d9a-c918-8009-9042-d020bc2e1cb2
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include<algorithm>
using namespace std;


bool isFeasible(long long mid, const vector<long long> &c, long long n, long long k)
{
    long long groups = 0;
    vector<long long> remainder;
    remainder.push_back(0);
    for (long long i = 0; i < n; i++)
    {
        long long now_groups = (remainder[i] + c[i]) / mid; // Number of groups we can form with current age
        remainder.push_back(min((remainder[i] + c[i]) % mid ,c[i]));
        groups += now_groups;
        if (groups >= k)
            return true; // Early exit if we already have enough groups
    }
    return groups >= k;
}
int main() {
    int t;
    cin >> t; // Number of test cases
    vector<long long> results;

    while (t--) {
        long long n, k;
        cin >> n >> k;

        vector<long long> c(n);
        for (long long i = 0; i < n; i++) {
            cin >> c[i];
        }

        // Binary search for the maximum group size
        long long low = 1, high = 2 * *max_element(c.begin(), c.end()), best = 0;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (isFeasible(mid, c, n, k)) {
                best = mid; // Update best result
                low = mid + 1; // Search for larger group sizes
            } else {
                high = mid - 1; // Search for smaller group sizes
            }
        }

        results.push_back(best * k);
    }

    // Output all results
    for (long long result : results) {
        cout << result << endl;
    }

    return 0;
}