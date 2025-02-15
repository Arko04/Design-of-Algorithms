#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
using namespace std;

const int MAX = 1e6;

struct node
{
    int x;
    int y;

    // Overload the < operator to compare node objects
    bool operator<(const node &other) const
    {
        if (x != other.x)
            return x < other.x; // Compare x coordinates first
        return y < other.y;     // If x is the same, compare y coordinates
    }
};

int main()
{
    int row, col;
    cin >> row >> col;
    cin.ignore(); // Ignore the newline after dimensions input

    // Initialize the matrix
    vector<vector<char>> cell(row, vector<char>(col));
    vector<vector<int>> cell_country1(row, vector<int>(col, MAX));
    vector<vector<int>> cell_country2(row, vector<int>(col, MAX));
    vector<vector<int>> cell_country3(row, vector<int>(col, MAX));
    vector<vector<int>> result(row, vector<int>(col, MAX));

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
    // cout << "--------------------" << endl;
    // for (const auto &row : cell)
    // {
    //     for (const auto &ch : row)
    //     {
    //         cout << ch;
    //     }
    //     cout << endl;
    // }

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

    // Function to perform BFS for any country and fill the respective country grid
    auto bfs = [&](set<node> &country, vector<vector<int>> &cell_country)
    {
        queue<pair<node, int>> q;
        for (node v : country)
        {
            visited[v.x][v.y] = true;
            q.push({v, 0});
            cell_country[v.x][v.y] = 0;
        }

        while (!q.empty())
        {
            pair<node, int> point = q.front();
            q.pop();
            node u = point.first;
            int distance = point.second;

            if (u.x + 1 < row && !visited[u.x + 1][u.y] && cell[u.x + 1][u.y] != '#')
            {
                visited[u.x + 1][u.y] = true;
                q.push({(node){u.x + 1, u.y}, distance + 1});
                cell_country[u.x + 1][u.y] = distance + 1;
            }
            if (u.x - 1 >= 0 && !visited[u.x - 1][u.y] && cell[u.x - 1][u.y] != '#')
            {
                visited[u.x - 1][u.y] = true;
                q.push({(node){u.x - 1, u.y}, distance + 1});
                cell_country[u.x - 1][u.y] = distance + 1;
            }
            if (u.y + 1 < col && !visited[u.x][u.y + 1] && cell[u.x][u.y + 1] != '#')
            {
                visited[u.x][u.y + 1] = true;
                q.push({(node){u.x, u.y + 1}, distance + 1});
                cell_country[u.x][u.y + 1] = distance + 1;
            }
            if (u.y - 1 >= 0 && !visited[u.x][u.y - 1] && cell[u.x][u.y - 1] != '#')
            {
                visited[u.x][u.y - 1] = true;
                q.push({(node){u.x, u.y - 1}, distance + 1});
                cell_country[u.x][u.y - 1] = distance + 1;
            }
        }
    };

    // Perform BFS for each country
    bfs(country1, cell_country1);
    // Reset visited for next countries
    fill(visited.begin(), visited.end(), vector<bool>(col, false));
    bfs(country2, cell_country2);
    // Reset visited for next countries
    fill(visited.begin(), visited.end(), vector<bool>(col, false));
    bfs(country3, cell_country3);

    // Print the result for country1
    // cout << "--------------------" << endl;
    // for (const auto &row : cell_country1)
    // {
    //     for (const auto &d : row)
    //     {
    //         cout << d << " ";
    //     }
    //     cout << endl;
    // }

    // Print the result for country2
    // cout << "--------------------" << endl;
    // for (const auto &row : cell_country2)
    // {
    //     for (const auto &d : row)
    //     {
    //         cout << d << " ";
    //     }
    //     cout << endl;
    // }

    // Print the result for country3
    // cout << "--------------------" << endl;
    // for (const auto &row : cell_country3)
    // {
    //     for (const auto &d : row)
    //     {
    //         cout << d << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (cell_country1[i][j] == MAX ||
                cell_country2[i][j] == MAX ||
                cell_country3[i][j] == MAX)
                result[i][j] = MAX;
            else
                result[i][j] = cell_country1[i][j] + cell_country2[i][j] + cell_country3[i][j] - 2;
        }
    }
    // cout << "--------------------\n RESULTS: " << endl;
    // for (const auto &row : result)
    // {
    //     for (const auto &d : row)
    //     {
    //         cout << d << " ";
    //     }
    //     cout << endl;
    // }

    // Function to compute the minimum distance between two countries using BFS
    auto min_bfs = [&](set<node> &start_country, set<node> &target_country)
    {
        queue<pair<node, int>> q;
        vector<vector<bool>> min_visited(row, vector<bool>(col, false));
        for (node v : start_country)
        {
            min_visited[v.x][v.y] = true;
            q.push({v, 0});
        }

        while (!q.empty())
        {
            pair<node, int> point = q.front();
            q.pop();
            node u = point.first;
            int distance = point.second;

            // Check if the target country is reached
            if (target_country.find(u) != target_country.end())
            {
                return distance;
            }

            if (u.x + 1 < row && !min_visited[u.x + 1][u.y] && cell[u.x + 1][u.y] != '#')
            {
                min_visited[u.x + 1][u.y] = true;
                q.push({(node){u.x + 1, u.y}, distance + 1});
            }
            if (u.x - 1 >= 0 && !min_visited[u.x - 1][u.y] && cell[u.x - 1][u.y] != '#')
            {
                min_visited[u.x - 1][u.y] = true;
                q.push({(node){u.x - 1, u.y}, distance + 1});
            }
            if (u.y + 1 < col && !min_visited[u.x][u.y + 1] && cell[u.x][u.y + 1] != '#')
            {
                min_visited[u.x][u.y + 1] = true;
                q.push({(node){u.x, u.y + 1}, distance + 1});
            }
            if (u.y - 1 >= 0 && !min_visited[u.x][u.y - 1] && cell[u.x][u.y - 1] != '#')
            {
                min_visited[u.x][u.y - 1] = true;
                q.push({(node){u.x, u.y - 1}, distance + 1});
            }
        }
        return -1; // Return -1 if no path exists
    };
    int answer = -1;
    // Calculate the minimum distances
    int min_dist_1_to_2 = min_bfs(country1, country2);
    int min_dist_2_to_3 = min_bfs(country2, country3);
    int min_dist_1_to_3 = min_bfs(country1, country3);

    // cout << "Minimum distance from Country 1 to Country 2: " << min_dist_1_to_2 << endl;
    // cout << "Minimum distance from Country 2 to Country 3: " << min_dist_2_to_3 << endl;
    // cout << "Minimum distance from Country 1 to Country 3: " << min_dist_1_to_3 << endl;
    if (min_dist_1_to_2 == -1 ||
        min_dist_2_to_3 == -1 ||
        min_dist_1_to_3 == -1)
    {
        answer = -1;
    }
    else
    {
        vector<int> mins = {min_dist_1_to_2 - 1, min_dist_1_to_3 - 1, min_dist_2_to_3 - 1};
        sort(mins.begin(), mins.end());
        int min1 = mins[0] + mins[1];
        int min2 = MAX; // Initialize with the maximum value
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                min2 = min(min2, result[i][j]); // Update min2 with the smallest value
            }
        }
        answer = min(min1, min2);
    }
    cout << answer << endl;
    return 0;
}
