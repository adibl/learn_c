#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dirdcl(void);
int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main()
{
    int type;
    int last_type;
    char temp[MAXTOKEN];
    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if (last_type == '*')
                    sprintf(temp, "*%s", out);
                else
                    sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
            last_type = type;
        }
        remove_last_paran(&out);
        printf("%s\n", out);
    }
    return 0;
}

void remove_last_paran(char *str)
{
    char *start = str;
    char temp;
    while (*str != '\0')
        str++;
    if(*--str == ')' && *(str - 1) != '(')
    {
        while (*start != '(')
            start++;
        while (start != str) {
            temp = *(start + 1);
            *start = *(start + 1);
            *(start + 1) = temp;
            start++;
        }
        *--start = '\0';
        return 0;
    }
    else
        return -1;
}

int gettoken(void)
{                               /* return next token */
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t');
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';);
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

int prev = ' ';

int getch()
{
    int temp = (prev != ' ') ? prev : getchar();
    prev = ' ';
    return temp;
}

void ungetch(int c)
{
    if (prev != ' ') {
        printf("error: run over ungetch prev %d", prev);
    }
    prev = c;
}
