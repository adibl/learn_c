#include <stdio.h>
#include <string.h>

void reverse2(char s[]);

void main()
{
    char st[] = "abcd";
    printf("%s ", st);
    reverse2(st);
    printf("%s\n", st);

    char st2[] = "12345";
    printf("%s ", st2);
    reverse2(st2);
    printf("%s\n", st2);
}

void reverse2(char s[])
{
    static int i = 0;
    static int mid;
    static int slen;
    if (i == 0) {
        slen = strlen(s) - 1;
        mid = slen / 2;
    }
    char c = s[i];
    s[i] = s[slen - i];
    s[slen - i] = c;
    i++;
    if (i <= mid)
        reverse2(s);
    else {
        i = 0;
    }

}
