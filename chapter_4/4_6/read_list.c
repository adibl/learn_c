#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define VARIABLE '1'
#define VARIABLESET '2'
#define  ERRORVALUE '3'
#define NOTINRANGE -1
#define BUFSIZE 100


int getch(void);
void ungetch(int);
double get_value(char c);

int getop(char s[])
{
    int i, c;
    double return_val;
    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (c >= 'A' && c <= 'Z') {
        if ((c = getchar()) == '=')
            return VARIABLESET;
        else {
            ungetch(c);
            return VARIABLE;
        }
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        s[++i] = c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return '-';
        }
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}


char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void get_string(char s[])
{
    int i, c;
    i = 0;
    while ((s[++i] = c = getch()) != ' ' && c != '\t' && c != '\n');
    ungetch(s[i]);
    s[i] = '\0';
}


#define NUMOFLETTERS 26

double variables[26] = {0};
double variables_is[26] = {0};

double get_value(char c)
{
    if (c >= 'A' && c <= 'Z') {
        if (variables_is[c - 'A'] != 0)
        return variables[c - 'A'];
        else
            return NOTINRANGE;
    }
    else
        return NOTINRANGE;
}

double set_variable(char c, double num) {
    variables[c - 'A'] = num;
    variables_is[c - 'A'] = 1;
}
