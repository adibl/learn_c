#include <stdio.h>

#define SAPERATOR '-'
#define RANGES "azAZ09\0"

void expand_ranges(char s[], char t[]);

main()
{
    char t[100];
    expand_ranges("1-8a-c*text*a-z&text&a-c-e", t);
    printf("%s\n", t);

}


void expand_ranges(char s[], char t[])
{
    int i, j;    
    char prev, next;
    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if (s[i + 1] == SAPERATOR) {
            prev = s[i];
            next = s[i+2];
            if ((prev >= 'a' && prev <= 'z' && next >= prev )||
                (prev >='A' && prev <= 'Z' && next >= prev )||
                prev >= '0' && prev <='9' && next >= prev) {
                for (char c = prev; c <= next; c+=1)
                    t[j++] = c;
                i+=2;
            }
            else 
                t[j++] = s[i];
            
        }
        else 
            t[j++] = s[i];
    }
    t[j] = '\0';
}

