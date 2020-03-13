#include <stdio.h>
#define MAXLINE 100
#define TAB '\t'
int tabstop;
tabstop = 8;

int getline2(char line[], int maxline);
int calc_spaces(int len);

main()
{
    int len, i;
    char line[MAXLINE];
    int num_of_spaces;
    int word_len;
    word_len = 0;
    while ((len = getline2(line, MAXLINE)) > 0){
        for (i = 0; line[i] != '\0'; i++){
            if (line[i] == TAB){
                num_of_spaces = calc_spaces(word_len);
                for (; num_of_spaces > 0; num_of_spaces--)
                    putchar(' ');
                word_len = 0;
            }
            else
            {
                putchar(line[i]);
                ++word_len;
            }
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


int calc_spaces(int len)
{
    return tabstop - (len % tabstop);
}
