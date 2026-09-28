#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // For write()
using namespace std;

// Function to calculate the result based on conditions
string calc_function(int a, int b, int c, int d, string s) {
    int countH = 0, countP = 0, countHP = 0, countPH = 0;

    // Count occurrences of 'H' and 'P'
    for (char ch : s) {
        if (ch == 'H') {
            countH++;
        } else {
            countP++;
        }
    }

    // Count adjacent pairs 'HP' and 'PH'
    for (size_t j = 0; j < s.length() - 1; j++) {
        if (s[j] == 'H' && s[j + 1] == 'P') {
            countHP++;
        } else if (s[j] == 'P' && s[j + 1] == 'H') {
            countPH++;
        }
    }

    // Check conditions for validity
    if (countP != (b + c + d) || countH != (a + c + d) || countHP < c || countPH < d) {
        return "NO\n";
    }

    countP -= (c + d);
    countH -= (c + d);

    // Final condition check
    if (countH != a || countP != b) {
        return "NO\n";
    } else {
        return "YES\n";
    }
}

// Optimized function to write strings to stdout
void prints(const string& s) {
    write(STDOUT_FILENO, s.c_str(), s.length());
}

int main() {
    int n;
    cin >> n;
    vector<string> result;

    // Process each test case
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        string s;
        cin >> a >> b >> c >> d >> s;
        result.push_back(calc_function(a, b, c, d, s));
    }

    // Output all results
    for (const string& res : result) {
        prints(res);
    }

    return 0;
}
