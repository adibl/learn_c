#include <stdio.h>

void to_literal(char s[], char t[]);
void to_real(char s[], char t[]);

main()
{
    char to_find[100];
    to_literal("asd\ntab\t", to_find);
    printf("%s\n", to_find);
    to_real("asd\\ntab\\twagj", to_find);
    printf("%s\n", to_find);
}

void to_literal(char s[], char t[]) 
{
    int i;
    int j = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        switch(s[i])
        {
            case '\t': 
                t[j++] = '\\';
                t[j++] = 't';
                break;
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            default:
                t[j++] = s[i];
        }
    }
   t[j] = '\0'; 
}

void to_real(char s[], char t[]) 
{
    int i;
    int j = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '\\') {
            i++;
            switch(s[i])
            {
                case 't': 
                    t[j++] = '\t';
                    break;
                case 'n':
                    t[j++] = '\n';
                    break;
            }
        }
        else
            t[j++] = s[i];
    }
   t[j] = '\0'; 
}
