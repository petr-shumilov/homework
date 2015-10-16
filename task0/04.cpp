#include <iostream>

using namespace std;

const int _size = 1e3;

int main()
{
    int n;
    cin >> n;
    int a[_size], cnt = 0;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        if (!a[i])
            cnt++;
    cout << cnt;
    return 0;
}
