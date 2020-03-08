#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);
void print_binary(unsigned x);
unsigned setbits(unsigned x, int p, int n, unsigned y);

main()
{
    unsigned a, b;
    a = 110;
    b = 10;
    print_binary(a);
    print_binary(b);
    print_binary(setbits(a, 2, 2, b));
    print_binary(setbits(158, 5, 3, 29));
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned setbits(unsigned x, int p, int n,unsigned y)
{
    unsigned part_y = (~(~0 << n) & y) << (p + 1 - n);
    unsigned part_x = getbits(x, p, n) << (p + 1 - n);
    return (x ^ part_x) | part_y;
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
