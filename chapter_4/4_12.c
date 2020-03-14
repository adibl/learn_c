#include <stdio.h>

void itoa(int num, char result[], int base);

void main()
{
    char result[100];
    itoa(100, result, 10);
    printf("%d:%s\n\n", 100, result);
    itoa(14, result, 16);
    printf("%d:%s\n\n", 14, result);
    int a = -923476;
    itoa(a, result, 10);
    printf("%d\n%s\n\n", a, result);

}

void itoa(int num, char result[], int base)
{
    static int i = 0;
    static int count = 0;
    static char numbers[] = "0123456789abcdef";
        count++;
    if (num < 0) {
        result[i++] = '-';
        num = - num;
    }
    if (num / base != 0) {
        itoa(num / base, result, base);
    }
    result[i++] = numbers[num % base];
    count--;
    if (count == 0) {
        result[i++] = '\0';
        i = 0;
    }
}

