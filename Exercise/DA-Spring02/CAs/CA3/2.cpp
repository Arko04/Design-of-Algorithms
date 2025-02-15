#include <iostream>
#include <vector>
using namespace std;

void
Floyd_Warshall(vector<vector<int>>& A, int& n)
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
            }
        }
    }
}

int
main()
{
    int n, m;
    cin >> n;
    vector<vector<int>> A(n, vector<int>(n));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int w;
            cin >> w;
            A[i][j] = w;
        }
    }

    cin >> m;

    Floyd_Warshall(A, n);

    for(int i = 0; i < m; i++)
    {
        int f, r, u;
        cin >> f >> r >> u;
        int fru_time = A[f][r] + A[r][u];
        int fu_time = A[f][u];
        cout << fru_time << " " << fru_time - fu_time << endl;
    }

    return 0;
}
