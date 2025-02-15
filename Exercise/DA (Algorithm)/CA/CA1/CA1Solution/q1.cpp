#include <iostream>

using namespace std;

const int MAXN = 5e3+22 ;

int n, towers[MAXN];

// Solve question for towers[l:r) which towers colored up to "height" before
int solve(int l, int r, int height = 0)
{
	if (l >= r) 
		return 0;

	// Find minimum height
	int min_tower_index = l;
	for (int i=l+1; i<r; i++)
		if (towers[min_tower_index] > towers[i])
			min_tower_index=i;
	
	// Calculate answer1 : color all towers vertically
	int answer1 = r-l;

	// Calculate answer 2 : color horizontally up to minimum height
	// 	and solve recursively two parts  
	int answer2 = towers[min_tower_index]-height
		+ solve(l, min_tower_index, towers[min_tower_index])
		+ solve(min_tower_index+1, r, towers[min_tower_index]);

	return min(answer1, answer2);
}

int main()
{
	cin >> n;
	for (int i=0; i<n; i++)
		cin >> towers[i];

	cout << solve(0, n);

	return 0;
}