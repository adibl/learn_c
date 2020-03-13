#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void clear(void);
double top(void);
void swap(void);
void duplicate(void);
double dmod(double num, double mod);

main()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
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
                push(dmod(pop() , op2));
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
                
        }
        
    }
    return 0;
    
}

double dmod(double x, double y) {
    return x - (int)(x/y) * y;
}
