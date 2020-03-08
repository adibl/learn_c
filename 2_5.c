#include <stdio.h>

int any(char string[], char to_find[]);

main()
{
    printf("%d\n", any("1234567890", "971"));
    printf("%d\n", any("12345178901", "971"));
    printf("%d\n", any("2345178901", "971"));
    printf("%d\n", any("1605", "489"));

}

int any(char string[], char to_find[])
{
    int i, j;
    for (i = 0; string[i] != '\0'; i++) {
        j = 0;
        while (to_find[j++] != '\0')
            if (string[i] == to_find[j])
                return i;
    }
    return -1;
    
}
