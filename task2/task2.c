#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char n1[100], n2[100];
    memset(n1, '0', sizeof(char) * 100);
    memset(n2, '0', sizeof(char) * 100);
    n1[0] = n1[1] = n1[2] = 1;
    n2[0] = n2[4] = n2[2] = 1;
    int i = 0;
    while (n1[i] == n2[i] && i < 100)
        ++i;
    if (n1[i] > n2[i])
        printf("1");
    else if (n1[i] < n2[i])
        printf("-1");
    else
        printf("0");
    return 0;
}
