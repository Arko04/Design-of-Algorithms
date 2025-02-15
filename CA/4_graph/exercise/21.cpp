#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
const int MAX = 1e7;
struct node
{
    int x;
    int y;
};

int main()
{
    int row, col;
    cin >> row >> col;
    cin.ignore(); // Ignore the newline after dimensions input

    // Initialize the matrix
    vector<vector<char>> cell(row, vector<char>(col, MAX));

    // Read the input map
    for (int i = 0; i < row; i++)
    {
        string line;
        getline(cin, line); // Read an entire row as a string
        for (int j = 0; j < col; j++)
        {
            cell[i][j] = line[j];
        }
    }

    // Print the map to verify input
    cout << "--------------------" << endl;
    for (const auto &row : cell)
    {
        for (const auto &ch : row)
        {
            cout << ch;
        }
        cout << endl;
    }

    // Vectors to store positions of different types of cells
    vector<node> country1, country2, country3, roads, blocked;

    // Identify cells for each type
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (cell[i][j] == '1')
            {
                country1.push_back({i, j});
            }
            else if (cell[i][j] == '2')
            {
                country2.push_back({i, j});
            }
            else if (cell[i][j] == '3')
            {
                country3.push_back({i, j});
            }
            else if (cell[i][j] == '.')
            {
                roads.push_back({i, j});
            }
            else if (cell[i][j] == '#')
            {
                blocked.push_back({i, j});
            }
        }
    }

    // Queue for BFS, storing each node and its distance
    queue<pair<node, int>> q;

    return 0;
}
