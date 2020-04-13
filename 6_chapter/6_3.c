#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcmp(const char*, const char*);

int getword(char* word, int lim);

struct tnode {
    char* word;
    struct inode* numbers;
    struct tnode* right;
    struct tnode* left;
};
struct inode {
    int number;
    struct inode* right;
    struct inode* left;
};

struct tnode* addtree(struct tnode*, char*, int);
struct tnode* get_deth(struct tnode* root);
void treeprint(struct tnode*);
char* ignore_words[] = { "the", "if", "for", "it", "is", "and", "was", "you", "" };

int main(int argc, char* argv[])
{
    struct tnode* root;
    root = NULL;
    int line_number = 1;
    char word[100];
    char c;
    char** p;
    while ((c = getword(word, 100)) != -1) {
        if (c == '\n')
            line_number++;
        else if (isalnum(word[0])) {
            p = ignore_words;
            while (*p[0] != '\0')
                if (strcmp(*(p++), word) == 0)
                    goto next_word;
            root = addtree(root, word, line_number);
        }
    next_word:;
    }
    treeprint(root);
}

void itreeprint(struct inode*);

void treeprint(struct tnode* p)
{
    if (p == NULL)
        return;
    treeprint(p->right);
    itreeprint(p->numbers);
    printf(" %s\n", p->word);
    treeprint(p->left);
}

void itreeprint(struct inode* p)
{
    if (p == NULL)
        return;
    itreeprint(p->right);
    printf("%d,", p->number);
    itreeprint(p->left);
}

struct tnode* talloc(void);
char* strdup(const char* s);
struct inode* add_number(struct inode* p, int num);

/* addtree: add a node with w, at or below p */
struct tnode* addtree(struct tnode* p, char* w, int num)
{
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->left = p->right = NULL;
        p->numbers = NULL;
        p->numbers = add_number(p->numbers, num);
    } else if (strcmp(p->word, w) < 0)
        p->left = addtree(p->left, w, num);
    else if (strcmp(p->word, w) > 0)
        p->right = addtree(p->right, w, num);
    else {
        p->numbers = add_number(p->numbers, num);
    }
    return p;
}

struct inode* add_number(struct inode* p, int line_num)
{
    if (p == NULL) {
        p = (struct inode*)malloc(sizeof(struct inode));
        p->number = line_num;
        p->left = p->right = NULL;
    } else if (line_num > p->number)
        p->right = add_number(p->right, line_num);
    else if (line_num < p->number)
        p->right = add_number(p->left, line_num);
    return p;
}

#include <stdlib.h>
/* talloc: make a tnode */
struct tnode* talloc(void)
{
    return (struct tnode*)malloc(sizeof(struct tnode));
}

/* getword: get next word or character from input */
int getword(char* word, int lim)
{
    int c, getch2(void);
    void ungetch2(int);
    char* w = word;
    while (isspace(c = getch2()) && c != '\n')
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalnum(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch2())) {
            ungetch2(*w);
            break;
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
