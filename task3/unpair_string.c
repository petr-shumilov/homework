#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _SIZE 255

char cur[_SIZE], str[_SIZE];

int main()
{
    while(1)
    {
        memset(str, _SIZE, 0);
        scanf("%s", cur);
        if (!strcmp(cur, "exit"))
            break;
        int i;
        for (i = 0; i < _SIZE; i++)
            str[i] = (str[i] ^ cur[i]);
    }
    printf("%s\n", str);
    return 0;
}