// https://chatgpt.com/share/674538fa-eec4-8009-8a75-71af1215fe59
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
string after_swapping_function(long long n, long long k, vector<long long> &heights)
{
    for (long long i = 0; i < n - k; ++i)
    {
        bool valid = false;
        for (long long j = i + 1; j < min(i + k + 1, n); ++j)
        {
            if (heights[j] < heights[i])
            {
                valid = true;
                break;
            }
        }
        if (!valid)
        {
            return "NO"; // If any position fails the condition after the swap, return NO
        }
    }

    return "YES";
}
string canBeautifyBooks(long long n, long long k, vector<long long> &heights)
{
    bool swapped = false;

    // Step 1: Iterate through each book
    for (long long i = 0; i < n - k; ++i)
    {
        bool valid = false;

        // Step 2: Check if there is any book within the next k positions with a smaller height
        for (long long j = i + 1; j < i + k + 1; ++j)
        {
            if (heights[j] < heights[i])
            {
                valid = true;
                break;
            }
        }

        if (valid)
        {
            continue; // Move to the next book
        }

        // Step 3: If no valid book is found, try to swap
        else
        {
            // cout << i << endl;
            long long minIndex = -1;
            long long minValue = 100000000000;

            // Find the last minimum book in the range (i+1) to (i+k)
            for (long long j = i + 1; j < i + k + 1; ++j)
            {
                if (heights[j] <= minValue)
                {
                    minValue = heights[j];
                    minIndex = j;
                }
            }

            // If no valid book to swap with, return "NO"
            if (minIndex == -1)
            {
                return "NO";
            }

            // Swap the books at i and minIndex
            for (long long j = i + k + 1; j < n; ++j)
            {
                // if (heights[j] < heights[i])
                // {
                for (long long z = i + 1; z < i + k + 1; ++z)

                {
                    swap(heights[j], heights[z]);
                    if (after_swapping_function(n, k, heights) == "YES")
                    {
                        return "YES";
                    }
                    else
                    {
                        swap(heights[j], heights[z]);
                    }
                }
                // }
            }

            return "NO";
        }
    }

    // Step 4: After the swap, check if the row satisfies the "beautiful" condition
    // for (long long i = 0; i < n - 1; ++i)
    // {
    //     bool valid = false;
    //     for (long long j = i + 1; j < min(i + k + 1, n); ++j)
    //     {
    //         if (heights[j] < heights[i])
    //         {
    //             valid = true;
    //             break;
    //         }
    //     }
    //     if (!valid)
    //     {
    //         return "NO"; // If any position fails the condition after the swap, return NO
    //     }
    // }

    return "YES"; // If all checks pass, return YES
}

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> heights(n);
    for (long long i = 0; i < n; ++i)
    {
        cin >> heights[i];
    }

    cout << canBeautifyBooks(n, k, heights) << endl;
    return 0;
}
