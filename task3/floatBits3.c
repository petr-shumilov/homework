#include <stdio.h>

const int _SIZE = 23;

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

typedef struct ans ans;

struct ans
{
    int S, M, E;
};

ans float_bits(float a)
{
    float *dump = &a;
    int *tmp = (int*)dump;
    int __int = *tmp;

    int S = !!(__int >> 31);
    int M = __int & ((1 << 23) - 1);
    int E = (__int << 1) >> 24;

    ans res;
    res.S = S;
    res.M = M;
    res.E = E;
    return res;
}

void print(ans a)
{
    if (a.E == 255)
    {
        if (a.M > 0)
            printf("NaN");
        else if (!a.M)
        {
            if (a.S)
                printf("-inf");
            else
                printf("inf");
        }
        return;
    }
    printf("(-1)^%d * 1.", a.S);
    print_M(a.M);
    printf(" * 2^(%d - 127)", a.E);
}

int main()
{
    float a;
    scanf("%f", &a);
    print(float_bits(a));
    return 0;
}
