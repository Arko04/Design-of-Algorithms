#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair <int,int> pii;
typedef pair <int,pii> piii;
#define X first
#define Y second
#define mp(x,y) make_pair(x,y)
#define Size(x) (int)(x).size()

const int N = 10000 + 5;
vector <piii> edl;
int pa[N];

int fp(int x){
	return !pa[x]?x:pa[x] = fp(pa[x]);
}

bool add(int x,int y){
	x = fp(x), y = fp(y);
	if(x != y)
		pa[x] = y;
	return x != y;
}

int main(){
	ios::sync_with_stdio(false);
	int n, t, ans = 0;
	cin >> n;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin >> t,
			edl.push_back(mp(t,mp(i,j)));
	for(int i=1;i<=n;++i)
		cin >> t,
		edl.push_back(mp(t,mp(0,i)));
	sort(edl.begin(),edl.end());
	for(int i=0;i<Size(edl);++i)
		if(add(edl[i].Y.X, edl[i].Y.Y))
			ans += edl[i].X;
	cout << ans;
	return 0;
}