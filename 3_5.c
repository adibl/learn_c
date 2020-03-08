#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define SEQANCE "0123456789abcdef"
void reverse(char s[]);
void itob(int number, char s[], int base);

main()
{
    char s[1000];
    itob(157, s, 16);
    printf("%s\n", s);
    itob(157, s, 13);
    printf("%s\n", s);
}

void itob(int number, char s[], int base) {
    int add;
    int i = 0;
    do {
       add = abs(number % base); 
       s[i++] = SEQANCE[add];
    } while (number /=base);
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
