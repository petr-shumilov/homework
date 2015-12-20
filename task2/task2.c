#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void strrev(char *s)
{
    int i, len = strlen(s);
    for (i = 0; i < len / 2; i++)
    {
        char tmp = s[len - i - 1];
        s[len - i - 1] = s[i];
        s[i] = tmp;
    }
}

int main()
{
    char n1[SIZE] = "1010", n2[SIZE] = "101";
    strrev(n1);
    strrev(n2);
    int i;
    for (i = strlen(n1); i < SIZE; ++i)
        n1[i] = '0';
    for (i = strlen(n2); i < SIZE; ++i)
        n2[i] = '0';
    
    i = SIZE - 1;
    while (i > 0)
    {
        if (n1[i] > n2[i])
        {
            printf("1");
            return 0;
        }
        else if (n1[i] < n2[i])
        {
            printf("-1");
            return 0;
        }
        i--;
    }
    printf("0");
    return 0;
}
