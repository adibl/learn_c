#include <stdio.h>
#define MAXLINE 1000
#define TAB '\t'
#define YES 1
#define NO 0
#define ONELINE 2

char STARTCOMMENT[3] = {'/', '*', '\0'};
char ENDCOMMENT[3] = {'*', '/', '\0'} ;
char ONELINECOMMENT[3] = {'/', '/', '\0'};

int getline2(char line[], int maxline); //one line comment
int is_pattern(char pattern[], char line[], int index); /*test comment*/
/*test comment*/

/*
   test multiline comment
   line 2*/
#define TEST "//must be seen"
#define TEST '*/ must be seen */'
main()
{
    int len, i;
    char line[MAXLINE];
    int start_index, last_index;
    int is_in_comment, is_in_string;
    is_in_comment = NO;
    while ((len = getline2(line, MAXLINE)) > 0){
        if (is_in_comment == ONELINE)
            is_in_comment = NO;
        for (i = 0; i < len; i++)
        {
            if (is_in_string == NO){
            if (is_pattern(STARTCOMMENT, line, i) == YES)
            {
                is_in_comment = YES;
                ++i;
                ++i;
            }
            else if (is_pattern(ENDCOMMENT, line, i) == YES)
            {
                is_in_comment = NO;
                ++i;
                ++i;
            }
            else if (is_pattern(ONELINECOMMENT, line, i) == YES)
            {
                is_in_comment = ONELINE;
                ++i;
                ++i;
            }
            }
            if (line[i] == '\"' || line[i] == '\'')
                if (is_in_string == NO)
                    is_in_string = YES;
                else
                    is_in_string = NO;
            if (is_in_comment == NO)
                putchar(line[i]);

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

int is_pattern(char pattern[], char line[], int index)
{
    int i;
    for (i = 0;pattern[i] != '\0' && line[i + index] != '\0'; i++)
        if (pattern[i] != line[i + index])
            return NO;
    if (line[i + index] == '\0' && pattern[i] != '\0')
        return NO;
    return YES;
}

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
