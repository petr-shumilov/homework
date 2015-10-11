#include <stdio.h>

int get_byte(x, n)
{
    return (x >> (n << 3)) & 255;
}

int main()
{
    int x, n;
    scanf("%d%d", &x, &n);
    printf("%d", get_byte(0x12345678,1));
    return 0;
}

