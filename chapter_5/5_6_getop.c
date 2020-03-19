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
int isdigit(int arg);
int strcmp(const char *str1, const char *str2);

int getline2(char s[], int lim);
void reverse(char s[]);

int getop(char *line, char *result);
void push(double);
double pop(void);
void clear(void);
double top(void);
void get_string(char s[], char result[]);

double get_value(char c);
void set_variable(char var, double value);

void swap(void);
void duplicate(void);

char getch(void);
void ungetch(char c);

double dmod(double num, double mod);

main()
{
    int type;
    double op2, op;
    char line[MAXOP];
    char result[MAXOP];
    char var;
    double prev = 0;
    while (getline2(line, MAXOP) > 0) {
        reverse(line);
        while ((type = getop(line, result)) != EOF && type != '\n') {
            switch (type) {
            case NUMBER:
                push(atof(result));
                break;
            case ERRORVALUE:
                printf("var %c dont have value\n", result[0]);
                break;
            case VARIABLE:
                if (get_value(result[0]) == NOTINRANGE)
                    printf("var %c dont have value\n", result[0]);
                else
                    push(get_value(result[0]));
                break;
            case '#':
                push(prev);
                break;
            case VARIABLESET:
                var = result[0];
                type = getop(line, result);
                if (type == NUMBER)
                    set_variable(var, atof(result));
                else if (type == VARIABLE)
                    set_variable(var, get_value(result[0]));
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
                get_string(line, result);
                if (strcmp(result, "sin") == 0)
                    push(sin(pop()));
                else if (strcmp(result, "sqrt") == 0) {
                    if (top() > 0)
                        push(sqrt(pop()));
                } else
                    printf("error: unknown command %s.\n", result);
                break;
            }
        }
        prev = top();
        printf("\t%.8g\n", pop());
    }

    return 0;
}

double dmod(double x, double y)
{
    return x - (int) (x / y) * y;
}

#define BUFSIZE 100

int getop(char *s, char *result)
{
    int c;
    double return_val;
    while(*s)
        s++;
    while ((*result = c = *--s) == ' ' || c == '\t');
    result++;
    if (c >= 'A' && c <= 'Z') {
        if ((*result++ = c = *--s) == '=')
            return_val = VARIABLESET;
        else {
            s++;
            result--;
            return_val = VARIABLE;
        }
    } else if (!isdigit(c) && c != '.' && c != '-') {
        return_val = c;
    }
    else {
        if (c == '-') {
            c = *--s;
            if (!isdigit(c) && c != '.') {
                s++;
                result--;
                return_val = '-';
                *s = '\0';
                result = '\0';
                return return_val;
            }
        }
        if (isdigit(c))
            while (isdigit(*result++ = c = *--s));
        if (c == '.')
            while (isdigit(*result++ = c = *--s));
        if (c != EOF) {
            s++;
            result--;
        }
        return_val = NUMBER;
        *s = '\0';
        *result = '\0';
        return return_val;
    }
    *s = '\0';
    *result = '\0';
    return return_val;
}

char prev = ' ';

char getch()
{
    char temp = (prev != ' ') ? prev : getchar();
    prev = ' ';
    return temp;
}

void ungetch(char c)
{
    prev = c;
}

void get_string(char s[],char result[])
{
    int i, c;
    i = 0;
    int j = 1;
    for (i = 0; s[i] != '\0'; i++)
        ;
    while ((result[j++] = c = s[--i]) != ' ' && c != '\t' && c != '\n');
    i++;
    j--;
    s[i] = '\0';
    result[j] = '\0';
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


int getline2(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
