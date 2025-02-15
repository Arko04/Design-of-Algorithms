#include <iostream>

using namespace std;

const int MAXN = 5 * 1000 + 10;

int a[MAXN], mn[MAXN][MAXN];

// minimum number of strokes needed to paint walls from i to j, and d horizontal strokes before
int solve(int l, int r, int d) {
	if (r - l < 1) return 0;

	int m = mn[l][r];
	int res = min(r - l, solve(l, m, a[m]) + solve(m + 1, r, a[m]) + a[m] - d);
	return res;
}

int main () {
	ios::sync_with_stdio(false);

	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];	
	}

	for (int i = 0; i < n; i++) {
		mn[i][i + 1] = i;
		for (int j = i + 1; j < n; j++) {
			mn[i][j + 1] = a[j] < a[mn[i][j]] ? j : mn[i][j];
		}
	}

	cout << solve(0, n, 0) << endl;
	return 0;
}

