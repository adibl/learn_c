#include <stdio.h>
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
    }
    else
        printf("stack size is less then 2\n");
}

void clear(void)
{
    sp = 0;
}
