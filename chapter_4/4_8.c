#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE '1'
#define VARIABLESET '2'
#define ERRORVALUE '3'
#define NOTINRANGE -1

double sin(double x);
double sqrt(double arg);
int strcmp(const char *str1, const char *str2);
int isdigit(int arg);

int getop(char[]);
void push(double);
double pop(void);
void clear(void);
double top(void);
void get_string(char s[]);

double get_value(char c);
void set_variable(char var, double value);

void swap(void);
void duplicate(void);

int getch(void);
void ungetch(int c);

double dmod(double num, double mod);

main()
{
    int type;
    double op2, op;
    char s[MAXOP];
    char var;
    double prev = 0;
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case ERRORVALUE:
            printf("var %c dont have value\n", s[0]);
            break;
        case VARIABLE:
            if (get_value(s[0]) == NOTINRANGE)
                printf("var %c dont have value\n", s[0]);
            else
                push(get_value(s[0]));
            break;
        case '#':
            push(prev);
            break;
        case VARIABLESET:
            var = s[0];
            type = getop(s);
            if (type == NUMBER)
                set_variable(var, atof(s));
            else if (type == VARIABLE)
                set_variable(var, get_value(s[0]));
            else if (type == '?')
                set_variable(var, top());
            else
                printf("not valid variable set\n");
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '?':
            printf("\ttop:%.8g\n", top());
            break;
        case '!':
            clear();
            break;
        case '~':
            swap();
            break;
        case '^':
            duplicate();
            break;
        case '%':
            op2 = pop();
            push(dmod(pop(), op2));
            break;
        case '\n':
            prev = top();
            printf("\t%.8g\n", pop());
            break;
        default:
            get_string(s);
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "sqrt") == 0) {
                if (top() > 0)
                    push(sqrt(pop()));
            } else
                printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

double dmod(double x, double y)
{
    return x - (int) (x / y) * y;
}

#define BUFSIZE 100

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

char prev = ' ';

int getch()
{
    char temp = (prev != ' ') ? prev : getchar();
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

void get_string(char s[])
{
    int i, c;
    i = 0;
    while ((s[++i] = c = getch()) != ' ' && c != '\t' && c != '\n');
    ungetch(s[i]);
    s[i] = '\0';
}

#define NUMOFLETTERS 26

double variables[26] = { 0 };
double variables_is[26] = { 0 };

double get_value(char c)
{
    if (c >= 'A' && c <= 'Z') {
        if (variables_is[c - 'A'] != 0)
            return variables[c - 'A'];
        else
            return NOTINRANGE;
    } else
        return NOTINRANGE;
}

void set_variable(char c, double num)
{
    variables[c - 'A'] = num;
    variables_is[c - 'A'] = 1;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        return 0.0;
    }
}

double top(void)
{
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void duplicate(void)
{
    push(top());
}

void swap(void)
{
    if (sp > 2) {
        double c = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = c;
    } else
        printf("stack size is less then 2\n");
}

void clear(void)
{
    sp = 0;
}
