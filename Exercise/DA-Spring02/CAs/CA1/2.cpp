#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void conquer(int& ans, int start_ind, int mid_ind, int end_ind, vector<int>& arr);
void divide(int& ans, int start_ind, int end_ind, vector<int>& arr);
void update_ans(int& ans, int start_ind, int mid_ind, int end_ind, vector<int>& arr);


int main()
{
    int n, element;
    int ans = 0;

    cin >> n;

    vector<int> arr;

    for(int i = 0; i < n; i++)
    {
        cin >> element;
        arr.push_back(element);
    }

    divide(ans, 0, n - 1, arr);

    cout << ans << endl;

    return 0;
}

void conquer(int& ans, int start_ind, int mid_ind, int end_ind, vector<int>& arr)
{
    update_ans(ans, start_ind, mid_ind, end_ind, arr);

    vector<int> temp_arr(end_ind - start_ind + 1, 0);

    int i = start_ind;
    int j = mid_ind + 1;
    int k = 0; 

    while(i < mid_ind + 1 && j < end_ind + 1)
    {
        if (arr[i] > arr[j])
        {
            temp_arr[k] = arr[j];
            j++;
        }
        else
        {
            temp_arr[k] = arr[i];
            i++;
        }
        k++;
    }

    while(i < mid_ind + 1)
    {
        temp_arr[k] = arr[i];
        i++;
        k++;
    }

    while(j < end_ind + 1)
    {
        temp_arr[k] = arr[j];
        j++;
        k++;
    }

    k = 0;

    for(int i = start_ind; i < end_ind + 1; i++)
    {
        arr[i] = temp_arr[k];
        k++;
    }
}

void divide(int& ans, int start_ind, int end_ind, vector<int>& arr)
{
    if(start_ind - end_ind >= 0)
    {
        return;
    }

    int mid_ind = (start_ind + end_ind) / 2;

    divide(ans, start_ind, mid_ind, arr);
    divide(ans, mid_ind + 1, end_ind, arr);
    conquer(ans, start_ind, mid_ind, end_ind, arr);
}

void update_ans(int& ans, int start_ind, int mid_ind, int end_ind, vector<int>& arr)
{
    int j = mid_ind + 1;

    for(int i = start_ind; i < mid_ind + 1; i++)
    {
        while(j < end_ind + 1 && arr[i] > 2 * arr[j])
        {
            j++;
        }
        ans += j - (mid_ind + 1);
    }
}