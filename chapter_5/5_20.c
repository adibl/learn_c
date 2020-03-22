/*
 * 1. add const static type support
 * 2. add function variables support with all types suported by prev command
 * 3. stable to invalid input
 * bug: dont fail on const a (or any var without a name)
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, ERR };

int dcl(void);
int dirdcl(void);
int gettoken(void);
int getch_no_space(void);
void ungetch(int c);
int get_type(char *type);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char err[100];
char *types[] = { "const", "static", "" };

int main()
{
    while (gettoken() != EOF) {
        if (get_type(datatype) == 0) {
            printf("type problem\n");
            return 0;
        }
        if (dcl()) {
            printf("err: %s\n", err);
        }
        switch (tokentype) {
        case '(':
        case '[':
            printf("missing caaalosing brackets\n");
            break;
        case '*':
            printf("pointer to no object\n");
            break;
        case NAME:
            printf("name out of contex\n");
            break;
        case '\n':
            break;
        default:
            printf("general synmax error\n");
        }

        if (tokentype != '\n') {
            while (gettoken() != '\n');
        }
        printf("%s %s\n", out, datatype);
        token[0] = '\0';
        name[0] = '\0';
        datatype[0] = '\0';
        out[0] = '\0';
        err[0] = '\0';
    }
    return 0;
}

int dcl(void)
{
    if (tokentype == '\n')
        return 0;
    int ns;
    for (ns = 0; gettoken() == '*';) {  /* count *'s */
        if (tokentype == '*')
            ns++;
    }
    if (dirdcl())
        return -1;
    while (ns-- > 0)
        strcat(out, " pointer to");
    return 0;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void)
{
    if (tokentype == '\n')
        return 0;
    int type;
    char arr[100];
    if (tokentype == '(') {
/* ( dcl ) */
        if (dcl())
            return -1;
        if (tokentype != ')') {
            strcat(err, "missing closing brackets ");
            return -1;
        }
    } else if (tokentype == NAME) {
        strcat(out, token);
        strcat(out, ": ");
    } else {
        strcat(err, "expected name or closing brackent ");
        return -1;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS
           || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            arr[0] = '\0';
            strcat(out, "function(");
            while (tokentype != ')') {
                gettoken();
                if (tokentype == '\n')
                    return -1;
                if (get_type(arr) == 0) {
                    printf("type problem\n");
                    return -1;
                }
                if (dcl())
                    return -1;
                strcat(out, " ");
                strcat(out, arr);
                strcat(out, " ");
            }
            strcat(out, ") returns");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    return 0;
}

int gettoken(void)
{                               /* return next token */
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    c = getch_no_space();
    if (c == '(') {
        if ((c = getch_no_space()) == ')') {
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

int get_type(char type[])
{
    int is_copied = 0;
    type[0] = '\0';
    do {
        is_copied = 0;
        for (int i = 0; types[i][0] != '\0'; i++) {
            if (strcmp(types[i], token) == 0) {
                strcat(type, token);
                strcat(type, " ");
                is_copied = 1;
                break;
            }
        }
        if (is_copied == 0) {
            strcat(type, token);
            return 1;
        }
    } while (gettoken() == NAME);
    return 0;
}

int getch_no_space()
{
    int ch;
    int getch();
    while ((ch = getch()) == ' ');
    return ch;
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


