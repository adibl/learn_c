#include <stdio.h>

char *strncpy2(int n, char *t, char *s);
char *strncat2(int n, char *t, char *s);
int strncmp2(int n, char *t, char *s);

int main(void)
{
    char s[100] = "mystr";
    char *p;
    strncpy2(10, "abc", s);
    printf("%s\n",s);
    strncpy2(2, "12345", s);
    printf("%s\n",s);
    strncat2(10, "abc", s);
    printf("%s\n",s);
    printf("%d %d\n",strncmp2(2, "123", "123"), strncmp2(3, "123", "12x"));
    return 0;
}

char *strncpy2(int n, char *t, char *s)
{
    char *start = s;
    while(*s++)
        ;
    s--;
    for (; n > 0 && *t != '\0'; n--)
        *s++ = *t++;
    for (; n > 0; n--)
        *s++ = '\0';
    return start;
}

char *strncat2(int n, char *t, char *s)
{
    char *start = s;
    while(*s++)
        ;
    s--;
    for (; n > 0 && *t != '\0'; n--)
        *s++ = *t++;
    *s = '\0';
    return start;
}

int strncmp2(int n, char *t, char *s)
{
    for(; n >= 0 && *t == *s; n--)
        t++, s++;
    return *t - *s;
}
