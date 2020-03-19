#include <stdio.h>

int strend(char *s, char *t);

int main(void)
{
    char a[] = "pattern1 pat2";
    char b[] = "pat2";
    char c[] = "xat2";
    printf("%d %d", strend(a, b), strend(a, c));
    return 0;
}

int strend(char *s, char *t)
{
    char *start = t;
    while (*s++)
        ;
    while (*t++)
        ;
    while (*--s == *--t && t >= start)
        ;
    return t < start;
}
