// https://chatgpt.com/share/672f4a00-6518-8003-86a5-ebe29163cf6b
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> statue;
    statue.push_back(1);
    for (int i = 1; i <= n; i++)
    {
        int m;
        cin >> m;
        statue.push_back(m);
    }
    statue.push_back(1);
    vector<vector<int> > dp(n + 2, vector<int>(n + 2, 0));

    for (int length = 1; length <= n; ++length) { 
        for (int i = 1; i <= n - length + 1; ++i) { 
            int j = i + length - 1;
           
            for (int k = i; k <= j; ++k) {
                dp[i][j] = max(dp[i][j], 
                               dp[i][k - 1] + dp[k + 1][j] + statue[i - 1] * statue[k] * statue[j + 1]);
            }
        }
    }

    cout << dp[1][n];
    return 0;

}
