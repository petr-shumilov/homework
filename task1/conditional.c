#include <stdio.h>

int conditional(int x, int y, int z)
{
    x = (x | (~x + 1)) >> 31;
    return (x & y) | (~x & z);
}

int main()
{
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    printf("%d", conditional(x, y, z));
    return 0;
}

