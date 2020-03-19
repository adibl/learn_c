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

int isdigit(int arg);
int strcmp(const char *str1, const char *str2);
double atof(const char *str);

int is_number(char *line);

int getop(char line[], char result[]);
void push(double);
double pop(void);
double top(void);

double dmod(double num, double mod);

int main(int argc, char *argv[])
{
    char *line;
    int op2;
    for (int i = 1; i < argc; i++) {
        line = argv[i];
        if (is_number(line) == 1)
            push(atof(line));
        else {
            if (line[1] != '\0')
                printf("undifined action %s\n", line);
            else {
                switch (line[0]) {
                case '+':
                    push(pop() + pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/': case '\\':
                    op2 = pop();
                    push(pop() / op2);
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                default:
                    printf("action %s is not valid\n", line);
                        break;
                }
            }
        }
    }
    printf("result:%f\n", pop());

}

double dmod(double x, double y)
{
    return x - (int) (x / y) * y;
}

#define BUFSIZE 100

int getop(char s[], char result[])
{
    int i, c, j;
    j = 0;
    double return_val;
    for (i = 0; s[i] != '\0'; i++);
    while ((result[0] = c = s[--i]) == ' ' || c == '\t');
    j++;
    if (c >= 'A' && c <= 'Z') {
        if ((result[j++] = c = s[--i]) == '=')
            return_val = VARIABLESET;
        else {
            i++;
            j--;
            return_val = VARIABLE;
        }
    } else if (!isdigit(c) && c != '.' && c != '-') {
        return_val = c;
    } else {
        if (c == '-') {
            c = s[--i];
            if (!isdigit(c) && c != '.') {
                i++;
                j--;
                return_val = '-';
                s[i] = '\0';
                result[j] = '\0';
                return return_val;
            }
        }
        if (isdigit(c))
            while (isdigit(result[j++] = c = s[--i]));
        if (c == '.')
            while (isdigit(result[j++] = c = s[--i]));
        if (c != EOF) {
            i++;
            j--;
        }
        return_val = NUMBER;
        s[i] = '\0';
        result[j] = '\0';
        return return_val;
    }
    s[i] = '\0';
    result[j] = '\0';
    return return_val;
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

int is_number(char *line)
{
    while(*line == ' ' || *line == '\t')
        line++;
    while(isdigit(*line))
        line++;
    if (*line == '.')
        line++;
    while(isdigit(*line))
        line++;
    if (*line == '\n')
        line++;
    return *line == '\0';
}
