#include <stdio.h>

//check x == 2^n
int isPower2(int x)
{
    int _x = (x & (x + ~0));
    return (1 & !_x) & !!x & ~(x >> 31);;
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", isPower2(x));
    return 0;
}

