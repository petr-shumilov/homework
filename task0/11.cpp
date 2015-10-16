#include <iostream>

using namespace std;

struct fib_matrix
{
    int a, b, c, d;
    fib_matrix(int a1, int b1, int c1, int d1) : a(a1), b(b1), c(c1), d(d1) {}
};

fib_matrix operator *(const fib_matrix x, const fib_matrix y)
{
    int a1 = x.a * y.a + x.b * y.c,
    b1 = x.a * y.b + x.b * y.d,
    c1 = x.c * y.a + x.d * y.c,
    d1 = x.c * y.b + x.d * y.d;
    return fib_matrix(a1, b1, c1, d1);
}

const fib_matrix start = fib_matrix(1, 1, 1, 0);

fib_matrix bin_pow(int n)
{
    if (n == 1)
        return start;
    if (n % 2)
        return bin_pow(n - 1) * start;
    else
    {
        fib_matrix b = bin_pow(n / 2);
        return b * b;
    }
}

int main()
{
    int n;
    cin >> n;
    fib_matrix ans = bin_pow(n);
    cout << ans.a;
    return 0;
}
