#include <stdio.h>
#include <string.h>

void reverse(char *s);
size_t strlen(const char *s);

int main(void)
{
    char s[] = "mystr";
    printf("%ld\n", strlen(s));
    printf("%s", s);
    reverse(s);
    printf(" %s\n", s);
    return 0;
}

void reverse(char *s)
{
    char *p;
    char temp;
    p = s + strlen(s) - 1;
    while (p >= s) {
        temp = *p;
        *p = *s;
        *s = temp;
        s++, p--;
    }
}
