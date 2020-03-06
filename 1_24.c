#include <stdio.h>
#define MAXLINE 1000
#define YES 1
#define NO 0
char OPENERS[4] = {'(', '{', '[', '\0'};
char CLOSERS[4] = {')', '}', ']', '\0'};


int getline2(char line[], int maxline); 
int push(char value);
int index_in_list(char options[], char ch);
char pop();
char top();
int is_empty();

char stack[MAXLINE];
int stack_end = 0;

main()
{
    int len, i;
    char line[MAXLINE];
    int open_index, close_index;
    int line_num = 0;
    int is_in_comment = NO;
    int is_in_string = NO;
    int is_in_double_string = NO;
    int is_in_one_line_comment = NO;
    int is_in_code;
    while ((len = getline2(line, MAXLINE)) > 0){
        ++line_num;
        if (is_in_one_line_comment == YES)
            is_in_one_line_comment = NO;
        for (i = 0; i < len; i++)
        {
            is_in_code = is_in_comment == NO &&  is_in_string == NO && is_in_double_string == NO && is_in_one_line_comment == NO;
            if (is_in_code){
                open_index = index_in_list(OPENERS, line[i]);
                close_index = index_in_list(CLOSERS, line[i]);
                if (close_index != -1)
                {
                    if (close_index == index_in_list(OPENERS, top()))
                    {
                        pop();
                    }
                    else
                        if (close_index != open_index)
                            printf("close character %c one in line %d:%d mismatch character %c\n", line[i],line_num, i + 1, top());
                }
                else if (open_index != -1)
                {
                    push(line[i]);
                    if (line[i] == '\'' || line[i] == '\"')
                        is_in_string = YES;

                }
            }
            if (line[i] == '\\')
                ++i;
            else if (line[i] == '/' && line[i + 1] == '*')
                is_in_comment = YES;
            else if (line[i] == '*' && line[i + 1] == '/')
                is_in_comment = NO;
            else if (line[i] == '\'')
                is_in_string = xor(is_in_string);
            else if (line[i] == '\"')
                is_in_double_string = xor(is_in_double_string);
            else if (line[i] == '/' && line[i + 1] == '/')
                is_in_one_line_comment = YES;
        } 
    } 
    while (is_empty() == NO)
    {
        printf("unclosed brackets %c\n", pop());
    }
    if (is_in_comment == YES)
        printf("unclosed comment\n");
    if (is_in_string == YES)
        printf("unclosed \' string\n")  ;
    if (is_in_double_string == YES)
        printf("unclosed \" string\n");
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

int push(char value)
{
    extern char stack[];
    extern int stack_end;
    if (stack_end >= MAXLINE)
        return -1;
    stack[stack_end + 1] = value;
    ++stack_end;
    return 0;
}

char pop()
{
    extern char stack[];
    extern int stack_end;
    --stack_end;
    return stack[stack_end + 1];
}

char top()
{
    extern char stack[];
    extern int stack_end;
    return stack[stack_end];
}

int is_empty()
{
    extern int stack_end;
    if (stack_end == 0)
        return YES;
    return NO;

}

int index_in_list(char options[], char ch)
{
    int i; 
    for (i = 0; options[i] != '\0'; i++)
        if (options[i] == ch)
            return i;
    return -1;
}

int xor(int exp)
{
    if (exp == YES)
        return NO;
    if (exp == NO)
        return YES;
}
