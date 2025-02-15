#include <iostream>
using namespace std;

const int MAXN = 1 * 1000 + 10;

int a[MAXN];
int dp[MAXN][2];
// dp[i][0]: number of zigzag subsequences ending at index i and last element is smaller than its previous
// dp[i][1]: number of zigzag subsequences ending at index i and last element is greater than its previous

int main () {
	ios::sync_with_stdio(false);

	int n; cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	
	int ans = 1;
	dp[0][0] = dp[0][1] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[j] > a[i]) {
				dp[i][0] = max(dp[i][0], dp[j][1] + 1);
			}
			if (a[j] < a[i]) {
				dp[i][1] = max(dp[i][1], dp[j][0] + 1);
			}
		}
		ans = max(ans, max(dp[i][0], dp[i][1]));
	}
	cout << n - ans << endl;
	return 0;
}

