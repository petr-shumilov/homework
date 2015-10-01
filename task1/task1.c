#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
    return (x >> 31) | 1;
}

//get n byte
int get_byte(x, n)
{
    return (x >> ((n + (~0)) << 3)) & 255;
}

//get 001001...100
int third_bit()
{
    return (36) | (73 << 8) | (73 << 17) | (36 << 24) ;
}

//check entry x in 2^n 
int fit_bits(int x, int n)
{
    return !(x >> n);
}

int main()
{
    srand(time(0));
    int a = rand();
    int b = rand();
    printf("(%d & %d) == %d ; bit_and(%d, %d) == %d\n", a, b, (a & b), a, b, bit_and(a, b));
    printf("(%d | %d) == %d ; bit_or(%d, %d) == %d\n", a, b, (a | b), a, b, bit_or(a, b));
    printf("(%d ^ %d) == %d ; bit_xor(%d, %d) == %d\n", a, b, (a ^ b), a, b, bit_xor(a, b));
    printf("((%d > 0) ? 1 : -1) == %d ; sign(%d) == %d\n", a, ((a > 0) ? 1 : -1), a, sign(a));
    //printf("\n", a, ((a > 0) ? 1 : -1), a, sign(a));
    printf("(00100100100100100100100100100100 == %d) == %d\n", third_bit(), (0b00100100100100100100100100100100 == third_bit()));
    //int q = (int)(pow(2.0, 2.0));
    //printf("((%d < pow(2, %d)) ? 1 : 0) == %d ; fit_bits(%d, %d) == %d\n", a, b % 32, ( a < q), a, b % 32, fit_bits(a, b % 32));
    return 0;
}

