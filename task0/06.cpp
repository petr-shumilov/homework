#include <iostream>
#include <algorithm>

using namespace std;

inline string str_to_lower(string &s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

inline string full_trim(string &s)
{
    int i = 0;
    while (i < int(s.size()))
        if (s[i] == ' ')
            s.erase(i, 1);
        else
            ++i;
    return s;
}

inline bool check(string &a)
{
    int n = a.size();
    for (int i = 0; i < n / 2; ++i)
        if (a[i] != a[n - i - 1])
            return 0;
    return 1;
}

int main()
{
    string s;
    getline(cin, s);
    s = full_trim(s);
    s = str_to_lower(s);
    check(s) ? cout << "YES" : cout << "NO";
    return 0;
}
