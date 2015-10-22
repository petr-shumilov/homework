#include <stdio.h>

union checker
{
    int a;
    char bytes[sizeof(int)];
};

int endianCheck()
{
    union checker x;
    x.a = 1;
    int first_byte = x.bytes[0];
    return first_byte;
}

int main()
{
    printf("%d", endianCheck());
    return 0;
}
