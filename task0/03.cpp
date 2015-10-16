#include <iostream>

using namespace std;

int bin_pow(int a, int n)
{
    if (!n)
        return 1;
    if (n % 2)
        return bin_pow(a, n - 1) * a;
    else
    {
        int b = bin_pow(a, n / 2);
        return b * b;
    }
}

int main()
{
    int a, n;
    cin >> a >> n;
    if (n < 0)
        cout << 1.0 / double(bin_pow(a, (-1) * n));
    else
        cout << bin_pow(a, n);
    return 0;
}
