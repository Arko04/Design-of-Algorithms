#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string after_swapping_function(int n, int k, vector<int>& heights)
{
        for (int i = 0; i < n - 1; ++i) {
        bool valid = false;
        for (int j = i + 1; j < min(i + k + 1, n); ++j) {
            if (heights[j] < heights[i]) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            return "NO"; // If any position fails the condition after the swap, return NO
        }
    }

    return "YES";
}
string canBeautifyBooks(int n, int k, vector<int>& heights) {

    // Step 1: Iterate through each book
    for (int i = 0; i < n - 1; ++i) {
        bool valid = false;
        
        // Step 2: Check if there is any book within the next k positions with a smaller height
        for (int j = i + 1; j < min(i + k + 1, n); ++j) {
            if (heights[j] < heights[i]) {
                valid = true;
                break;
            }
        }

        if (valid) {
            continue; // Move to the next book
        }

        // Step 3: If no valid book is found, try to swap
        else {
            int minIndex = -1;
            
            // Find the last minimum book in the range (i+1) to (i+k)
            for (int j = i + k + 1; j < min(i + k + 1, n); ++j) {
                if (heights[j] < heights[i]) {
                    minIndex = j;
                    swap(heights[i], heights[minIndex]);
                    if(after_swapping_function(n , k , heights) == "YES")
                    {
                        return "YES";
                    }
                    else{
                        swap(heights[i], heights[minIndex]);
                        minIndex = -1;
                    }
                }
            }

            // If no valid book to swap with, return "NO"
            if (minIndex == -1) {
                return "NO";
            }
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    cout << canBeautifyBooks(n, k, heights) << endl;
    return 0;
}
