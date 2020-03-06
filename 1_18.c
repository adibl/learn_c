#include <stdio.h>
#define MAXLINE 1000

int getline2(char line[], int maxline);
int removeblank(char line[]);

main()
{
    int len;
    char line[MAXLINE];
    while ((len = getline2(line, MAXLINE)) > 0){
        len = removeblank(line);
        if (len > 1)
            printf("%s", line);

    }
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

int removeblank(char s[])
{
    char c;
    int i;
    int count_move;
    int len;
    for (i = 0; s[i] != '\0'; i ++)
        ;
    len = i;
    count_move = 0;
    for (i = 0; s[i] == ' ' || s[i] == '\t'; i++)
        ++count_move;
    for (i = 0; i <= len - count_move; i++)
        s[i] = s[i + count_move];
    return len - count_move;

}
