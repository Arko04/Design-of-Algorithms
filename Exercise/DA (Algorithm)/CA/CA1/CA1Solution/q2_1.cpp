#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int N = 1e5+22;

int n, jump_len, stones[N];
int used_stones[N];

bool binary_search_check(int frogs)
{
	memset(used_stones, 0, sizeof(used_stones));
	
	queue<int> frogs_queue;
	frogs_queue.push(0);
	used_stones[0] = frogs;
	 
	for (int i=1; i<=n; i++)
	{
		if (stones[i]==0) 
			continue;
		int frogs_ready=0; // number of frogs which ready to jump on stones[i]

		while (frogs_queue.size())
		{
			int frogs_index = frogs_queue.front();
			int frogs_count = used_stones[frogs_index];
			if (frogs_count==0)
			{
				frogs_queue.pop();
				continue;
			}

			if (frogs_index+jump_len < i) 
				return false;

			if (frogs_ready+frogs_count <= stones[i])
			{
				frogs_ready += frogs_count;
				used_stones[frogs_index] = 0;
				frogs_queue.pop();
			}
			else
			{
				used_stones[frogs_index] -= stones[i]-frogs_ready;
				frogs_ready = stones[i];
				break;
			}
		}
		if (frogs_ready && i!=n) 
		{
			frogs_queue.push(i);
			used_stones[i] = frogs_ready;
		}
	}	
	return frogs_queue.size()==0;
}

int main()
{
	cin >> n >> jump_len;
	
	for (int i=1; i<n; i++)
		cin >> stones[i];
	stones[n] = 1e9;

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