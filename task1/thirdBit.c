#include <stdio.h>

int third_bit()
{
    return (36) | (73 << 8) | (73 << 17) | (36 << 24) ;
}

int main()
{
    printf("%d", third_bit());
    return 0;
}

