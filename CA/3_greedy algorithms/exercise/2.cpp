#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isValid(int a, int b, int c, int d, const string &s)
{
    if (s.empty())
    {
        return a == 0 && b == 0 && c == 0 && d == 0;
    }
    char last = s[s.length() - 1];
    if (s.length() == 1)
    {
        if (last == 'H')
        {
            return isValid(a - 1, b, c, d, s.substr(0, s.size() - 1));
        }
        else
        {
            return isValid(a, b - 1, c, d, s.substr(0, s.size() - 1));
        }
    }
    char one_to_last = s[s.length() - 2];

    if (last == 'H' && one_to_last == 'H')
    {
        return isValid(a - 1, b, c, d, s.substr(0, s.length() - 1));
    }
    else if (last == 'P' && one_to_last == 'P')
    {
        return isValid(a, b - 1, c, d, s.substr(0, s.length() - 1));
    }
    else if (last == 'H' && one_to_last == 'P')
    {
        return isValid(a - 1, b, c, d, s.substr(0, s.length() - 1)) or isValid(a, b, c, d - 1, s.substr(0, s.length() - 2));
    }
    else
    {
        return isValid(a, b - 1, c, d, s.substr(0, s.length() - 1)) or isValid(a, b, c - 1, d, s.substr(0, s.length() - 2));
    }
}

int main()
{
    int t;
    cin >> t;

    for(int i = 0; i < t; i++)
    {
        int a, b, c, d;
        string s;
        cin >> a >> b >> c >> d >> s;
        cout << ((isValid(a,b,c,d,s)) ? "Yes" : "No") << endl;
    }

    return 0;
}
