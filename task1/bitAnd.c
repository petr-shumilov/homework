#include <stdio.h>

int bit_and(int a, int b)
{
    return ~(~a | ~b);
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", bit_and(a, b));
    return 0;
}
