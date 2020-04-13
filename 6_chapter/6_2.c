#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcmp(const char*, const char*);

int get_variable(char*, int);

struct tnode {
    char* word;
    struct tnode* same_more;
    struct tnode* same_less;
    struct tnode* different_less;
    struct tnode* different_more;
};

struct tnode*
addtree(struct tnode*, char*);
struct tnode* get_deth(struct tnode* root);
void treeprint(struct tnode*);
int similar_size = 8;
void print_all_same(struct tnode* p);

int main(int argc, char* argv[])
{
    if (argc > 2) {
        if (strcmp(*++argv, "-s") == 0) {
            if (atoi(*++argv) != 0)
                similar_size = atoi(*argv);
            else
                printf("-s option must be intiger, ignore option\n");
        } else
            printf("option invalid\n");
    }
    struct tnode* root;
    root = NULL;
    char word[100];
    while (get_variable(word, 100) != -1)
        root = addtree(root, word);
    print_all_same(root);
}

int is_similar(char* str1, char* str2)
{
    return strncmp(str1, str2, similar_size);
}

void print_all_same(struct tnode* p)
{
    void print_same(struct tnode*);
    if (p == NULL)
        return;
    print_all_same(p->different_less);
    if (p->same_less != NULL || p->same_more != NULL) {
        printf("\n");
        print_same(p);
    }
    print_all_same(p->different_more);
}

void print_same(struct tnode* p)
{
    if (p == NULL)
        return;
    print_same(p->same_less);
    printf("%s \n", p->word);
    print_same(p->same_more);
}

struct tnode* talloc(void);
char* strdup(const char* s);
int is_similar(char*, char*);
/* addtree: add a node with w, at or below p */
struct tnode* addtree(struct tnode* p, char* w)
{
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->same_less = p->same_more = p->different_less = p->different_more = NULL;
    } else if ((cond = is_similar(p->word, w)) == 0) {
        if (strcmp(p->word, w) > 0)
            p->same_less = addtree(p->same_less, w);
        else if (strcmp(p->word, w) < 0)
            p->same_more = addtree(p->same_more, w);
    } else {
        if (strcmp(p->word, w) > 0)
            p->different_less = addtree(p->different_less, w);
        else if (strcmp(p->word, w) < 0)
            p->different_more = addtree(p->different_more, w);
    }
    return p;
}

#include <stdlib.h>
/* talloc: make a tnode */
struct tnode* talloc(void)
{
    return (struct tnode*)malloc(sizeof(struct tnode));
}

/* shod filter out unwanted wards */
int get_variable(char* var, int lim)
{
    int c, getch2();
    int getword(char*, int);
    int ignore_word;
    int in_comment = 0;
    int ret;
    do {
        ignore_word = 0;
        ret = getword(var, lim);
        if (ret == '#') {
            while ((c = getch2()) != '\n' && c != EOF)
                ;
            *var = '\0';
        }
        if (!isalpha(ret)) {
            ignore_word = 1;
            *var = '\0';
        }
        if (strcmp(var, "/*") == 0)
            in_comment = 1;
        if (strcmp(var, "*/") == 0) {
            in_comment = 0;
            ret = getword(var, lim);
        }
    } while ((ignore_word == 1 || in_comment == 1) && ret != -1);
    if (ignore_word == 1 || in_comment == 1)
        *var = '\0';
    return ret;
}

/* getword: get next word or character from input */
int getword(char* word, int lim)
{
    int c, getch2(void);
    int last_c;
    void ungetch2(int);
    char* w = word;
    while (isspace(c = getch2()))
        ;
    if (c != EOF)
        *w++ = c;
    if (c == '"' || c == '<') {
        if (c == '<')
            c = '>';
        for (; --lim > 0; w++)
            if ((*w = getch2()) == c) {
                w++;
                break;
            } else if (*w == EOF) {
                *w = '\0';
                return -1;
            }
    } else {
        if (c == '/') {
            last_c = c;
            c = getch2();
            if (c != '*') {
                ungetch2(c);
                c = last_c;
            } else {
                *w++ = c;
                *w = '\0';
                return word[0];
            }
        }
        if (c == '*') {
            last_c = c;
            c = getch2();
            if (c != '/') {
                ungetch2(c);
                c = last_c;
            } else {
                *w++ = c;
                *w = '\0';
                return word[0];
            }
        }
        if ((!isalnum(c)) && c != '"' && c != '#') {
            *w = '\0';
            return c;
        } else
            for (; --lim > 0; w++)
                if ((!isalnum(*w = getch2())) && *w != '_' && *w != '#') {
                    ungetch2(*w);
                    break;
                }
    }
    *w = '\0';
    return word[0];
}

int prev = ' ';

int getch2()
{
    int temp = (prev != ' ') ? prev : getchar();
    prev = ' ';
    return temp;
}

void ungetch2(int c)
{
    if (prev != ' ') {
        printf("error: run over ungetch prev %d", prev);
    }
    prev = c;
}
