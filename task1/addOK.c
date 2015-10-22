#include <stdio.h>

int addOK(int a, int b)
{
    return !(((a >> 31) ^ ((a + b) >> 31)) & ((b >> 31) ^ ((a + b) >> 31)));
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", addOK(a, b));
    return 0;
}
