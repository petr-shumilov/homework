#include <stdio.h>

int fit_bits(int x, int n)
{
    return !((x ^ (x >> 31)) >> (n + (~0)));
}

int main()
{
    int x, n;
    scanf("%d%d", &x, &n);
    printf("%d", fit_bits(x, n));
    return 0;
}

