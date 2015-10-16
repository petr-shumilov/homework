#include <iostream>
#include <vector>

using namespace std;

inline bool check(vector<int > &a)
{
    int n = a.size();
    for (int i = 0; i < n / 2; ++i)
        if (a[i] != a[n - i - 1])
            return 0;
    return 1;
}

int main()
{
    int n;
    cin >> n;
    vector <int > a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    check(a) ? cout << "YES" : cout << "NO";
    return 0;
}
