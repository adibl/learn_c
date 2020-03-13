#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'
#define VARIABLE '1'
#define VARIABLESET '2'
#define  ERRORVALUE '3'
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
void get_string(void);

double get_value(char c);
void set_variable(char var, double value);

void swap(void);
void duplicate(void);
double dmod(double num, double mod);
double get_value(char c);

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
            printf("prev:%f\n", prev);
            printf("\t%.8g\n", pop());
            break;
        default:
            get_string();
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

