#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);
void print_binary(unsigned x);
unsigned invert(unsigned x, int p, int n);

main()
{
    unsigned a;
    a = 110;
    print_binary(a);
    print_binary(invert(a, 5, 3));
    print_binary(invert(a, 7, 4));
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned invert(unsigned x, int p, int n)
{
    unsigned mask = (~(~0 << n)) << (p + 1 - n);
    return x ^ mask;
}

void print_binary(unsigned x)
{
    char array[16];
    int i;
    for (i = 0; i < 16; i++) {
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
