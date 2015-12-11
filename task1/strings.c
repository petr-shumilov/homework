#include <stdio.h>
#include <stdlib.h>

size_t strlen(const char *s)
{
    int len = 0;
    while (s[len++] != '\0');
    return len - 1;  
}

int strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    if (strlen(s1) == strlen(s2) && strlen(s2) == i)
        return 0;
    return (s1[i] < s2[i] ? -1 : 1);
}


void strcpy(char* s1, const char* s2)
{
    int i = -1;
    while (s2[++i] != '\0')
        *s1 = s2[i], ++s1;
}

void strctt(char* s1, const char* s2)
{
    while(*s1)
        s1++;
    while(*s2)
    {
      *s1 = *s2;
      s1++;
      s2++;
    }
    *s1 = '\0';
}

int main()
{
    /*char a[] = "abc";
    char b[] = "cde";
    strctt(a, b);
    printf("%s", a);
    //printf("%d", strcmp1("asda", "asdab"));*/
    return 0;
}