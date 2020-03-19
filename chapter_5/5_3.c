#include <stdio.h>

void strcat2(char *s, char *t);

int main(void)
{
    char a[100] = "string1;";
    char b[100] = "string2";
    strcat2(a,b);
    printf("%s\n",a);
    a[0] = '\0';
    strcat2(a,b);
    printf("%s\n",a);
    return 0;
}

void strcat2(char *s, char *t)
{
    while(*s)
        s++;
    while(*s++ = *t++)
        ;
}
