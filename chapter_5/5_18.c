/*
 * 1. recover from whitspaces inside of empty brackets
 * 2. prevent leaking prev line if error
 * 3. dont get dtack and finish the program on the first error
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, ERR };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch_no_space(void);
void ungetch(int c);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char err[100];

int main()
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);        /* is the datatype */
        out[0] = '\0';
        err[0] = '\0';
        token[0] = '\0';
        name[0] = '\0';
        dcl();
        switch (tokentype) {
        case '(':
        case '[':
            strcat(err, "missing closing brackets ");
            break;
        case '*':
            strcat(err, "pointer to no object ");
            break;
        case NAME:
            strcat(err, "name out of contex ");
            break;
        default:
            strcat(err, "general synmax error ");
        }

        if (tokentype != '\n')
            printf("err: %s\n", err);
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void)
{
    if (tokentype == ERR)
        return;
    int ns;
    for (ns = 0; gettoken() == '*';) {  /* count *'s */
        if (tokentype == '*')
            ns++;
    }
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    if (tokentype == ERR)
        return;
    int type;
    if (tokentype == '(') {
/* ( dcl ) */
        dcl();
        if (tokentype != ')')
            strcat(err, "missing closing brackets "), tokentype = ERR;
    } else if (tokentype == NAME)       /* variable name */
        strcpy(name, token);
    else
        strcat(err, "expected name or closing brackent "), tokentype = ERR;
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
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
