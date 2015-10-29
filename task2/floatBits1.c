#include <stdio.h>

union float_int
{
    int _int;
    float _float;
};

void float_bits(float a)
{
    union float_int tmp;
    tmp._float = a;
    int __int = tmp._int;

    int S = !!(__int >> 31);
    int M = __int & ((1 << 23) - 1);
    int E = (__int << 1) >> 24;

    if (E == 255) 
    {
        if (M > 0)
            printf("NaN");
        else if (!M)
        {
            if (S)
                printf("-inf");
            else
                printf("inf");
        }
        return;
    }
    printf("(-1)^%d * 1.%d * 2^(%d - 127)", S, M, E);
}

int main()
{
    float a;
    scanf("%f", &a);
    float_bits(a);
    return 0;
}
