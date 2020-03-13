#include <stdio.h>

void squeez(char string[], char remove[]);

main()
{
    char string[] = "1234567890169";
    char remove[] = "160";
    squeez(string, remove);
    printf("%s\n", string);
    char string2[] = "1111";
    char remove2[] = "160";
    squeez(string2, remove2);
    printf("%s\n", string2);
    return 0;
}

void squeez(char string[], char remove[])
{
    int i, j, string_len;
    string_len = 0;
    i = j = 0;
    while (string[string_len] != '\0')
        ++string_len;
    for(i = 0; remove[i] != '\0'; i++) {
        j = 0;
        for (j = 0; string[j] != '\0'; j++) {
            if (string[j] == remove[i])
                string[j] = '\0';
        }
    }
    int to_copy = 0;
    for (i = 0; i < string_len; i++)
        if (string[i] == '\0')
            to_copy++;
        else
            string[i - to_copy] = string[i];
    string[i - to_copy] = '\0';
}

