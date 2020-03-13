#include <stdio.h>
#include <math.h>

#define HEXBASE 16
int htoi(char hex[]);

main()
{
    printf("%d %d %d %d\n", htoi("fa\0"), htoi("10\0"), htoi("fF\0"), htoi("0xfa\0"));
}

int htoi(char hex[])
{
    int i = 0;
    int result = 0;
    int start_index = 0;
    if (hex[i] == '0' && (hex[i+1] == 'x' || hex[i+1] == 'X'))
        start_index = 2;
    for(i = start_index; hex[i] != '\0'; ++i) {
        if (hex[i] >= '0' && hex[i] <= '9')
            result = result * pow(HEXBASE, i - start_index) + hex[i] - '0';
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            result = result * pow(HEXBASE, i - start_index) + hex[i] - 'a' + 10;
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            result = result * pow(HEXBASE, i - start_index) + hex[i] - 'A' + 10;
    } 
    return result;
}

