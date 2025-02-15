#include <iostream>

using namespace std;
const int N = 1e5+22;

int n, jump_len, stones[N];
int partial_stones[N];

bool binary_search_check(int frogs)
{
	for (int i=jump_len; i<n; i++)
		if (frogs > partial_stones[i] - partial_stones[i - jump_len])
			return false;
	return true;
}

int main()
{
	cin >> n >> jump_len;
	
	for (int i=1; i<n; i++)
	{
		cin >> stones[i];
		partial_stones[i] = partial_stones[i-1] + stones[i];
	}

	int low=0, high=1e9+1, mid;
	while (high-low > 1)
	{
		mid = (low+high) / 2;
		if (binary_search_check(mid)) 
			low=mid;
		else 
			high=mid;
	}
	
	cout << low << endl;
	
	return 0;
}