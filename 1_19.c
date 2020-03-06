#include <stdio.h>
#define MAXLINE 100

int getline2(char line[], int maxline);
void reverse(char line[], int len);

main()
{
    int len;
    char line[MAXLINE];
    while ((len = getline2(line, MAXLINE)) > 0){
        if (len > 1)
        {
            reverse(line, len);
            printf("%s", line);
        }

    }
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
        ++len;
    }
    s[i] = '\0';
    return len;
}


void reverse(char line[], int len)
{
    char c;
    int i;
    for (i = 0; i < len / 2 ; i++) {
        c = line[i];
        line[i] = line[len - i -1];
        line[len - i - 1] = c;
    }
}

