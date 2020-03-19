#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn);

int main()
{
    float num;
    int res = getfloat(&num);
    printf("%d %f\n", res, num);
    res = getfloat(&num);
    printf("%d %f\n", res, num);
    return 0;
}

int getfloat(float *pn)
{
    int c, sign;
    int dividor = 1;
    while (isspace(c = getch()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);             /* it is not a number */
        return 0;

    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    if (!isdigit(c))
        c = 0;
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c == '.') {
        c = getch();
        for (; isdigit(c); c = getch()) {
            *pn = 10 * *pn + (c - '0');
            dividor *= 10;
        }
        *pn /= dividor;
    }
    if (c != EOF)
        ungetch(c);
    return c;
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
