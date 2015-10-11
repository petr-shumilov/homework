#include <stdio.h>

//check x == 2^n
int is_power2(int x)
{
    int _x = (x & (x + ~0));
    return ((_x & !1) | (1 & !_x)) & !(!x);
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", is_power2(x));
    return 0;
}

