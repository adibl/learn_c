#include <stdio.h>
#include <ctype.h>

int getword(char *word, int lim);

int main(void)
{
    char word[100];
    while (getword(word, 100) != -1)
        printf("%s\n", word);
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()));
    if (c != EOF)
        *w++ = c;
    if (c == '"' || c == '<') {
        if (c == '<')
            c = '>';
        for (; --lim > 0; w++)
            if ((*w = getch()) == c) {
                w++;
                break;
            } else if (*w == EOF) {
                *w = '\0';
                return -1;
            }
    } else {
        if ((!isalnum(c)) && c != '"' && c != '#') {
            *w = '\0';
            return c;
        } else
            for (; --lim > 0; w++)
                if ((!isalnum(*w = getch())) && *w != '_' && *w != '#') {
                    ungetch(*w);
                    break;
                }
    }
    *w = '\0';
    return word[0];
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
