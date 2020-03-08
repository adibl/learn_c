#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void print_binary(long x);
void itoa2(int n, char s[]);
void itoa_print(int n, char s[]);
void reverse(char s[]);

main()
{
    char s[100000];
    int a = -1 * pow(2, 31);
    itoa2(a , s);
    printf("%s\n", s);
    itoa_print(a, s);
    printf("%s\n", s);
    printf("%d\n", a);


}

void itoa_print(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (((n /= 10) != 0));
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void itoa2(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void print_binary(long x)
{
    int size = sizeof(x) * CHAR_BIT;
    char array[size];
    int i;
    for (i = 0; i < size; i++) {
        if (x & 0x1 == 1)
            array[i] = '1';
        else
            array[i] = '0';
        x = x >> 1;
    }
    for (; i >= 0; i--)
        putchar(array[i]);
    putchar('\n');
}

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
