#include <stdio.h>
#include <limits.h>

void print_binary(unsigned x);
int bitcount(unsigned x);

main()
{
    unsigned a;
    a = 110;
    print_binary(a);
    printf("%d\n", bitcount(a));
    printf("%d\n", bitcount(0));
}

int bitcount(unsigned x)
{
    int c;
    for (c = 0; x != 0; c++)
        x &= x - 1;
    return c;
}

void print_binary(unsigned x)
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
