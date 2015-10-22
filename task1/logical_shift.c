#include <stdio.h>

int logical_shift(int x, int n)
{
    return ((x & ~(1 << 31)) >> n) | ((x >> 31) & (1 << (31 + (~n + 1))));
}

int main()
{
    int x, n;
    scanf("%d%d", &x, &n);
    printf("%d", logical_shift(x, n));
    return 0;
}

