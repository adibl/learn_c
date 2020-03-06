#include <stdio.h>
#define MAXLINE 1000
#define MINPRINTLEN 80

int getline2(char line[], int maxline);
void copy(char to[], char from[]);

main()
{
    int len;
    int max;
    char line[MAXLINE];
    char c;
    max = 0;
    while ((len = getline2(line, MAXLINE)) > 0)
        if (len >= MINPRINTLEN) 
            printf("%s\n", line);
}

int getline2(char s[],int lim)
{
    int c, i, len;
    len = i = 0;
    while ((c=getchar())!=EOF && c!='\n')
    {
        if (i < lim - 2)
        {
            s[i] = c;
            ++i;
        }
        ++len;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
        ++len;
    }
    s[i] = '\0';
    return len;
}
