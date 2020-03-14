#include <stdio.h>

#define swap(t, a, b) {t z = a; a = b; b = z;}
#define dprint(expr) printf(#expr " = %g\n", expr)
main()
{
    int a2 = 7;
    int b2 = 8;
    char a3= 'a';
    char b3 = 'b';
    swap(int,a2,b2);
    swap(char, a3,b3);
    printf("%d %d\n", a2,b2);
    printf("%c %c\n",a3,b3);
    return 0;
}
