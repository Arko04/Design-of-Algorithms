#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void
make_graph(int& m, vector<vector<int>>& adj_ls)
{
    for(int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj_ls[u].push_back(v);
        adj_ls[v].push_back(u);
    }
}

void
DFS(int v, vector<int>& stack, vector<bool>& visited,
    vector<vector<int>>& adj_ls, vector<int>& cc)
{
    bool visit_time = true;

    if(!visited[v] && 
    find(stack.begin(), stack.end(), v) == stack.end())
    {
        stack.push_back(v);
    }

    for(auto u: adj_ls[v])
    {
        if(!visited[u] && 
        find(stack.begin(), stack.end(), u) == stack.end())
        {
            stack.push_back(u);
            DFS(stack.back(), stack, visited, adj_ls, cc);
            visit_time = false;
        }
    }

    if(visit_time)
    {
        int poped_v = stack.back();
        visited[poped_v] = true;
        cc.push_back(poped_v);
        stack.pop_back();
    }

    if(stack.empty())
        return;
    else
        DFS(stack.back(), stack, visited, adj_ls, cc);
}

vector<vector<int>> 
find_ccs(int& n, vector<vector<int>>& adj_ls)
{
    vector<vector<int>> ccs;
    vector<bool> visited (n + 1, false);
    visited[0] = true;

    for(int i = 1; i < n + 1; i++)
    {
        if(!visited[i])
        {
            vector<int> cc, stack;
            DFS(i, stack, visited, adj_ls, cc);
            ccs.push_back(cc);
        }
        else
            continue;
    }

    return ccs;
}

int
calc_total_visit_duration(vector<int>& cc, vector<int>& e)
{
    int total_visit_duration = 0;

    for(auto& forest: cc) 
        total_visit_duration += e[forest - 1];

    return total_visit_duration;
}

int
calc_total_biodiversity(vector<int>& cc, vector<int>& d)
{
    int total_biodiversity = 0;

    for(auto& forest: cc)
        total_biodiversity += d[forest - 1];

    return total_biodiversity;
}

int
solve_problem_using_dp(vector<vector<int>>& ccs, int& t,
                        vector<int>& e, vector<int>& d)
{
    int ccs_count = ccs.size();
    int dp[ccs_count + 1][t + 1];
    memset(dp, 0, sizeof(dp));
    int tmp_max = 0;

    for(int i = 1; i < ccs_count + 1; i++)
    {
        for(int j = 1; j < t + 1; j++)
        {
            tmp_max = dp[i - 1][j];
            int total_visit_duration = calc_total_visit_duration(ccs[i - 1], e);

            if(total_visit_duration <= j)
            {
                int total_biodiversity = calc_total_biodiversity(ccs[i - 1], d);
                if(dp[i - 1][j - total_visit_duration] + total_biodiversity > tmp_max)
                {
                    tmp_max = dp[i - 1][j - total_visit_duration] + total_biodiversity;
                }
            }

            for(auto forest: ccs[i - 1])
            {
                if(e[forest - 1] <= j)
                {
                    if(dp[i - 1][j - e[forest - 1]] + d[forest - 1] > tmp_max)
                    {
                        tmp_max = dp[i - 1][j - e[forest - 1]] + d[forest - 1];
                    }
                }
            }

            dp[i][j] = tmp_max;
        }
    }

    return dp[ccs_count][t];
}

int main()
{
    int n, m, t;
    cin >> n >> m >> t;

    vector<int> e, d;

    for(int i = 0; i < n; i++)
    {
        int ei;
        cin >> ei;
        e.push_back(ei);
    }

    for(int i = 0; i < n; i++)
    {
        int di;
        cin >> di;
        d.push_back(di);
    }

    vector<vector<int>> adj_ls, ccs;
    adj_ls.resize(n + 1);

    make_graph(m, adj_ls);
    ccs = find_ccs(n, adj_ls);

    cout << solve_problem_using_dp(ccs, t, e, d);

    return 0;
}