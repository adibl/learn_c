#include <stdio.h>
#define MAXLINE 1000
#define TAB '\t'

int max_len;
max_len = 30;
char split_by_1[3] = {' ', '\t', '\0'};
char split_by_2[4] = {',', ')', '(', '\0'};

int getline2(char line[], int maxline);
int get_index_of(char options[], char string[], int scan_len, int from_index);

main()
{
    int len, i;
    char line[MAXLINE];
    int last_index, start_index;
    int start_len;
    while ((len = getline2(line, MAXLINE)) > 0){
        start_len = len;
        start_index = 0;
        while (len > max_len)
        {
            last_index = get_index_of(split_by_1, line, max_len, start_index);
            if (last_index == -1)
                last_index = get_index_of(split_by_2, line, max_len, start_index);
            if (last_index == -1)
                last_index = start_index + max_len;
            if (last_index > start_len)
                last_index = start_len;
            for (i = start_index; i < last_index; i++)
                putchar(line[i]);
            putchar('\n');
            len = len - (last_index - start_index);
            start_index = last_index;

        }
        if (start_index < start_len)
        for (; line[start_index] != '\0'; start_index++)
            putchar(line[start_index]);
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


int get_index_of(char options[], char string[], int line_len, int from_index)
{
    int i, j, last_index;
    last_index = -1;
    for (i = from_index; i < from_index + line_len; i++)
    {
        for (j = 0; options[j] != '\0'; j++)
        {
            if (options[j] == string[i])
                last_index = i;
        } 
    }
    return last_index;
}
