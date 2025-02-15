#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
using namespace std;
const int MAX = 1e7;
// struct node
// {
//     int x;
//     int y;
// };

struct node {
    int x;
    int y;

    // Overload the < operator to compare node objects
    bool operator<(const node& other) const {
        if (x != other.x) return x < other.x;  // Compare x coordinates first
        return y < other.y;  // If x is the same, compare y coordinates
    }
};

int main()
{
    int row, col;
    cin >> row >> col;
    cin.ignore(); // Ignore the newline after dimensions input

    // Initialize the matrix
    vector<vector<char>> cell(row, vector<char>(col));

    vector<vector<int>> cell_country1(row, vector<int>(col, 0));
    vector<vector<int>> cell_country2(row, vector<int>(col, 0));
    vector<vector<int>> cell_country3(row, vector<int>(col, 0));

    vector<vector<bool>> visited(row, vector<bool>(col, false));
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
    set<node> country1, country2, country3, roads, blocked;

    // Identify cells for each type
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (cell[i][j] == '1')
            {
                country1.insert({i, j});
            }
            else if (cell[i][j] == '2')
            {
                country2.insert({i, j});
            }
            else if (cell[i][j] == '3')
            {
                country3.insert({i, j});
            }
            else if (cell[i][j] == '.')
            {
                roads.insert({i, j});
            }
            else if (cell[i][j] == '#')
            {
                blocked.insert({i, j});
            }
        }
    }

    // Queue for BFS, storing each node and its distance
    queue<pair<node, int>> q1;
    queue<pair<node, int>> q2;
    queue<pair<node, int>> q3;

    for (node v : country1)
    {
        visited[v.x][v.y] = true;
        q1.push({v, 0});
    }
    while (!q1.empty())
    {
        pair<node, int> point = q1.front();
        q1.pop();
        node u = point.first;
        int distance = point.second;
        if (u.x + 1 < row)
        {
            if (!visited[u.x + 1][u.y] && cell[u.x + 1][u.y] == '.')
            {
                visited[u.x + 1][u.y] = true;
                q1.push({(node){u.x + 1, u.y}, distance + 1});
                cell_country1[u.x + 1][u.y] = distance + 1;
            }
        }
        if (u.x - 1 >= 0)
        {
            if (!visited[u.x - 1][u.y] && cell[u.x - 1][u.y] == '.')
            {
                visited[u.x - 1][u.y] = true;
                q1.push({(node){u.x - 1, u.y}, distance + 1});
                cell_country1[u.x - 1][u.y] = distance + 1;
            }
        }
        if (u.y + 1 < col)
        {
            if (!visited[u.x][u.y + 1] && cell[u.x][u.y + 1] == '.')
            {
                visited[u.x][u.y + 1] = true;
                q1.push({(node){u.x, u.y + 1}, distance + 1});
                cell_country1[u.x][u.y + 1] = distance + 1;
            }
        }
        if (u.y - 1 >= 0)
        {
            if (!visited[u.x][u.y - 1] && cell[u.x][u.y - 1] == '.')
            {
                visited[u.x][u.y - 1] = true;
                q1.push({(node){u.x, u.y - 1}, distance + 1});
                cell_country1[u.x][u.y - 1] = distance + 1;
            }
        }
    }

    cout << "--------------------" << endl;
    for (const auto &row : cell_country1)
    {
        for (const auto &d : row)
        {
            cout << d << " ";
        }
        cout << endl;
    }
    return 0;
}
