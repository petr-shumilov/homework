#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* erase(char* str, char ch)
{
    char res[256];
    int i, k = 0;
    for (i = 0; i < strlen(str); ++i)
        if (str[i] != ch)
        {
            res[k] = str[i];
            k++;
        }
    res[k] = '\0';
    return res;
}

int main()
{
    char str[256], a;
    scanf("%s %c", &str[0], &a);
    printf("%s", erase(str, a));
    return 0;
}