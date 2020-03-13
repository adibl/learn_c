#include <stdio.h>
#include <limits.h>

void lower(char string[]);

main()
{
    char string[] = "abABkjDgj_";
    lower(string);
    printf("%s\n", string); 
}

void lower(char string[])
{
    for(int i = 0; string[i] != '\0';i++) {
        string[i] = (string[i] >= 'A' && string[i] <= 'F') ? string[i] - 'A' + 'a' : string[i];
    }

}
