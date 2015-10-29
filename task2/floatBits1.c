#include <stdio.h>

const int _SIZE = 23;

union float_int
{
    int _int;
    float _float;
};

void print_M(int a)
{
    int i;
    char res[_SIZE];
    for (i = 0; i < _SIZE; ++i)
    {
        res[i] = '0' + (a & 1);
        a >>= 1;
    }
    for (i = _SIZE - 1; i >= 0; i--)
        printf("%c", res[i]);
}

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
    printf("(-1)^%d * 1.", S);
    print_M(M);
    printf(" * 2^(%d - 127)", E);
}

int main()
{
    float a;
    scanf("%f", &a);
    float_bits(a);
    return 0;
}
