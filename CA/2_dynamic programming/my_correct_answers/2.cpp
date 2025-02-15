#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int n , m, k;
    cin >> n >> m >> k;
    double res[m + k + 1];
    for (int i = m; i <= m+k;i++)
    {
        if (i <= n)
        {
            res[i] = 1;
        }
        else{
            res[i] = 0;
        }
    }
    for (int i = m-1; i >= 0; i--)
    {
        double ans = 0;
        for (int j = i+1; j <= i+k; j++)
        {
            ans += res[j];
        }
        res[i] = ans / k;
    }
    cout << res[0];
    // cout << fixed << setprecision(5) << res[0] << endl;
    return 0;
}