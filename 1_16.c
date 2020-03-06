#include <stdio.h>
#define MAXLINE 10
int getline2(char line[], int maxline);
void copy(char to[], char from[]);
main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    char c;
    max = 0;
    while ((len = getline2(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        } 
    if (max > 0)
        printf("len:%d\n", max);
    printf("%s\n", longest);
    return 0;
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
    }
    s[i] = '\0';
    return len;
}
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
