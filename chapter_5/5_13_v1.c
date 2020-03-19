/* 
 * spare computation power because the input is directly moved to the array
 * and don't need to be copied secound time + no dinamic memory allocation
 * BUT problematic with huge line length
 * */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int atoi(const char *str);
int getline2(char s[], int lim);

int main(int argc, char *argv[])
{
    int n = 10;
    ++argv;
    if (argc > 1) {
        if (*argv[0] == '-') {
            n = -1 * atoi(*argv);

        } else
            fprintf(stderr, "no argument option %s\n", *argv);

    }
    char tail[n][MAXLINE];
    int len, i;
    i = 0;
    while ((len = getline2(tail[i], MAXLINE)) > 0) {
        if (i < n - 1)
            i++;
        else
            i = 0;

    }
    int boundery_i = i;
    for (; i < n; i++)
        printf("%s", tail[i]);
    for (i = 0; i < boundery_i; i++)
        printf("%s", tail[i]);
    return 0;

}

int getline2(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    if (c != EOF)
        s[i] = '\0';
    return i;

}
