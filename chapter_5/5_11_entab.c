#include <stdio.h>
#define MAXLINE 100
#define TAB '\t'
#define BLANK '#'
#define TABSIZE 4
#define MAXLEN 100

int defult_tabstop = 8;
int tabstopes[MAXLEN];

int atoi(char *s);

int getline2(char line[], int maxline);
int calc_spaces(int len);
int calc_tabs(int len, int *num_of_spaces);

int main(int argc, char *argv[])
{
    int *ptabstops = tabstopes;
    ++argv;
    for (; argc > 1; argc--, argv++) {
        if (atoi(*argv) == 0)
            printf("argument %s must be intiger\n", *argv);
        else {
            *ptabstops++ = atoi(*argv);
        }
    }
    *ptabstops = 0;
    int len, i;
    char line[MAXLINE];
    int num_of_spaces, num_of_tabs;
    int line_len;
    while ((len = getline2(line, MAXLINE)) > 0) {
        line_len = 0;
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == ' ') {
                num_of_spaces = 0;
                while(line[i] == ' ') {
                    num_of_spaces++;
                    i++;
                }
                i--;
                num_of_tabs = calc_tabs(line_len, &num_of_spaces);
                for (; num_of_tabs > 0; num_of_tabs--) {
                    putchar('%');
                    line_len += TABSIZE;
                }
                for (; num_of_spaces > 0; num_of_spaces--) {
                    putchar(BLANK);
                    ++line_len;
                }
            } else {
                putchar(line[i]);
                ++line_len;
            }
        }
    }
    return 0;
}

int getline2(char s[], int lim)
{
    int c, i, len;
    len = i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim - 2) {
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

int calc_tabs(int len, int *num_of_spaces)
{
    int *stops = tabstopes;
    int num_of_tabs = 0;
    while(*stops < len)
        stops++;
    while(*stops <= len + *num_of_spaces) {
        num_of_tabs++;
        stops++;
    }
    stops--;
    if (num_of_tabs > 0)
        *num_of_spaces += len - *stops;
    return num_of_tabs;
}
