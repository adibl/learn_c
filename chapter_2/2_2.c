#include <stdio.h>

main()
{
    char s[10];
    int lim = 10;
    int i;
    char c;
    for (i=0; i < lim-1; ++i) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        s[i] = c;
    }
    printf("\n%s\n", s);
    return 0;
}
