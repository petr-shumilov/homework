#include <iostream>
#include <vector>

using namespace std;

void sieve(int n)
{
    vector <bool > used(n, 0);
    for (int i = 2; i <= n; ++i)
        if (!used[i])
        {
            cout << i << " ";
            for (int j = i; j <= n; j += i)
                used[j] = 1;
        }
}

int main()
{
    int n;
    cin >> n;
    sieve(n);
    return 0;
}
