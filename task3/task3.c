#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int c, end = '\0', f = 0;
    FILE *in = fopen("input.txt", "r");
    while ((c = getc(in)) != EOF)
    {
        if (f)
            putchar(c);
        if (c == '\n')
            f = 0;
        if (c == '/' && end == '/')
            f = 1;
        end = c;
    }
    return 0;
}
