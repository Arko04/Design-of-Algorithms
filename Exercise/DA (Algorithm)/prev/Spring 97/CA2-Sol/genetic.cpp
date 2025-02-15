#include <iostream>
#include <map>

using namespace std;

int main () {
	ios::sync_with_stdio(false);

	map<char, int> cost;
	string s, t; cin >> s >> t;
	cin >> cost['A'] >> cost['C'] >> cost['G'] >> cost['T'];
	
	int ans = 1e9;
	for (int i = 0; i < s.size(); i++) {
		int k = i;
		int cur = 0;
		for (int j = 0; j < t.size(); j++) {
			if (k < s.size() && s[k] == t[j]) {
				k++;
			} else {
				cur += cost[t[j]];
			}
		}
		ans = min(ans, cur);
	}
	cout << ans << endl;
	return 0;
}

