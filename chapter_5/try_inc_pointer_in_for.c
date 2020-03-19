#include <stdio.h>

int main(void)
{
    char s[] = "0123456789";
    char *p = s;
    for (int i = 0; i < 4 && *p++ != '\0';i++)
        printf("%c", *p);
    /* gives loop from s[1] to s[4] */
    printf(" %c", *p);
    printf("\n");
    p = s;
    for (int i = 0; i < 4 && *p != '\0';i++) {
        p++;
        printf("%c", *p);
    }
    printf(" %c", *p);
    printf("\n");
    return 0;
}
