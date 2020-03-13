#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n);
void print_binary(unsigned x);

main()
{
    unsigned a;
    a = 110;
    print_binary(a);
    print_binary(rightrot(110, 1));
    print_binary(rightrot(110, 2));
    print_binary(rightrot(110, 3));
    print_binary(rightrot(110, 5));
    print_binary(rightrot(110, 7));

}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned rightrot(unsigned x, int n)
{
    return (x >> n) | (getbits(x, n, n) << (sizeof(x) * CHAR_BIT - n + 1));
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
