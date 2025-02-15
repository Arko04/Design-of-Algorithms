#include <bits/stdc++.h>
using namespace std;
 
int const MA = 11100 , MN = 111;
int n , k , a[MN] , b[MN] , ans = -1 , x[MN];
unordered_map <int , int> dp[2];
unordered_map <int , bool> is[2];
 
void smax(int &a , int b){
	a = max(a , b);
}
 
int main(){
	ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);
 
	cin >> n >> k;
	for(int i = 0 ; i < n ; i++)
		cin >> a[i] >> b[i];
 
	is[0][0] = 1;
	for(int i = 0 ; i <= n ; i++){
		for(int j = -MA ; j < MA ; j++){
			if(!is[ i%2 ][j]) 
                continue;
			
            int balance = a[i]-b[i]*k;
            smax(dp[ (i+1)%2 ][ j+balance ] , dp[ i%2 ][j] + a[i]);
			is[ (i+1)%2 ][ j+balance ] = 1;
 
			smax(dp[ (i+1)%2 ][j] , dp[ i%2 ][j]);
			is[ (i+1)%2 ][j] = 1;
		}
	}
    
	cout << (dp[n%2][0] ? dp[n%2][0] : -1) << '\n';
}