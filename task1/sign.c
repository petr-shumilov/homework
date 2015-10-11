#include <stdio.h>

//get sign
int sign(int x)
{
    int _x = !x;
    return  ((x >> 31) | 1) & (((_x & !0) | (0 & x)) + ~0);
}

int main()
{
    int a;
    scanf("%d", &a);
    printf("%d", sign(a));
    return 0;
}

