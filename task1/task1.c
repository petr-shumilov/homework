#include <stdio.h>

//bitwise and
int bit_and(int a, int b)
{
    return ~(~a | ~b);
}

//bitwise or
int bit_or(int a, int b)
{
    return ~(~a & ~b);
}

//bitwise xor
int bit_xor(int a, int b)
{
    return ~(~a | b) | ~(a | ~b); 
}

//get sign
int sign(int x)
{
    int _x = !x;
    return  ((x >> 31) | 1) & (((_x & !0) | (0 & x)) + ~0);
}

//get nth byte
int get_byte(x, n)
{
    return (x >> (n << 3)) & 255;
}

//get 001001...100
int third_bit()
{
    return (36) | (73 << 8) | (73 << 17) | (36 << 24) ;
}

//check entry x in [0; 2^n) 
int fit_bits(int x, int n)
{
    return !((x ^ (x >> 31)) >> (n + (~0)));
}

//bitwise shift 
int logical_shift(int x, int n)
{
    return (x >> n);
}

int conditional(int x, int y, int z)
{
    x = !!x;
    x |= x << 1;
    x |= x << 2;
    x |= x << 4;
    x |= x << 8;
    x |= x << 16;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return (x & y) | (~x & z);
}

//check x == 2^n
int is_power2(int x)
{
    int _x = (x & (x + ~0));
    return ((_x & !1) | (1 & !_x)) & !(!x);
}

int main()
{
    printf("sign(%d) = %d\n", -123, sign(-123));
    printf("sign(%d) = %d\n", 0, sign(0));
    printf("sign(%d) = %d\n", 34514, sign(34514));
    printf("getbyte(%d, %d) = %d\n", 0x12345678, 1, get_byte(0x12345678, 1));
    printf("third_bit() = %d\n", third_bit()); //TODO: to_bin()
    printf("fit_bits(%d, %d) = %d\n", 5, 3, fit_bits(5, 3));
    printf("fit_bits(%d, %d) = %d\n", -4, 3, fit_bits(-4, 3));
    printf("logical_shift(%d, %d) = %d\n", 0x8765432, 4, logical_shift(0x8765432, 4));
    printf("conditional(%d, %d, %d) = %d\n", 1, 123, 5, conditional(1, 123, 5));
    printf("conditional(%d, %d, %d) = %d\n", 0, 4, 5, conditional(0, 4, 5));
    printf("is_power2(%d) = %d\n", -1, is_power2(-1));
    printf("is_power2(%d) = %d\n", 0, is_power2(0));
    printf("is_power2(%d) = %d\n", 1, is_power2(1));
    printf("is_power2(%d) = %d\n", 7, is_power2(7));
    printf("is_power2(%d) = %d\n", 8, is_power2(8));
    return 0;
}
