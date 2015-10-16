#include <iostream>

using namespace std;

int main()
{
    string s, s1;
    cin >> s >> s1;
    int n = s.size(), m = s1.size(), ans = 0;;
    for (int i = 0; i < n; ++i)
    {
        int k = 0;
        while (s[i + k] == s1[k] && k < m)
        {
            k++;
        }
        if (k == m)
            ans++;
    }
    cout << ans;
    return 0;
}
