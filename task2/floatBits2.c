#include <stdio.h>

const int _SIZE = 23;

struct bit_field
{
    int M:23;
    int E:8;
    int S:1;
};

union float_int
{
    float _float;
    struct bit_field _bit_field;
};

typedef struct ans ans;

struct ans
{
    int S, M, E;
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

ans float_bits(float a)
{
    union float_int tmp;
    tmp._float = a;

    int S = tmp._bit_field.S;
    int M = tmp._bit_field.M;
    int E = tmp._bit_field.E;

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
