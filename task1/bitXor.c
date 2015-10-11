#include <stdio.h>

int bit_xor(int a, int b)
{
    return ~(~a | b) | ~(a | ~b); 
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", bit_xor(a, b));    
    return 0;
}

