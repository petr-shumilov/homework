#include <stdio.h>
#include <stdlib.h>

size_t strlen(const char *s)
{
    int len = 0;
    while (s[len++] != '\0');
    return len - 1;  
}

int strcmp1(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0')
    {
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
        else
            i++;
    }
    return 0;
}


void strcpy(char *s1, const char *s2)
{
    do
    {
        *s1++ = *s2;
    } while (*s2++);
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
    //char a[] = "abc";
    //char b[] = "cde";
    //strcpy(a, b);
    //printf("%s", a);
    //printf("%d", strcmp1("ab", "b"));
    return 0;
}