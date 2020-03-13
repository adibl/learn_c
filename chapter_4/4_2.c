#include <ctype.h>
#include <stdio.h>
#include <math.h>

double atof2(char s[]);
int atoi(char s[], int from);

main ()
{
    printf("%f\n", atof2(" 179.58"));
    printf("%f\n", atof2(" 179.58e-2"));
    printf("%f\n", atof2(" .00008e10"));
}

double atof2(char s[])
{
    double pow(double x, double y);
    double val, power;
    int i, sign;
    int enumber = 1;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power /= 10;
    }
    if(s[i] == 'e' || s[i] == 'E') {
        ++i;
        enumber = atoi(s, i);
        printf("%d\n", enumber);
    } 
    return sign * val * power * pow(10, enumber);
}

int atoi(char s[], int from)
{
    int i, n, sign;
    i = from;
    for (; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
        for (n = 0; isdigit(s[i]); i++)
            n = 10 * n + (s[i] - '0');
    return sign * n;
}
