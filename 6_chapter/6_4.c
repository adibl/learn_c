#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIM 100

struct tnode {
    int count;
    char* word;
    struct tnode* left;
    struct tnode* right;
};

struct tlist {
    struct tnode* current;
    struct tlist* next;
};

int strcmp(const char*, const char*);
struct tlist* list_root = NULL;

struct tnode* add_node(char* word, int count, struct tnode* root);
struct tlist* add_list_node(struct tnode* node, struct tlist* root, struct tlist* prev);
int update_word(char* word, int inc);
void print_pre_order(struct tnode* root);
int getword(char* word, int lim);
void print_list(struct tlist* root);
void insert_sorting(struct tnode * root);

int main(void)
{
    char word[LIM];
    struct tnode* root = NULL;
    while (getword(word, LIM) > 0) {
        if (word[0] == '\n' || word[0] == ' ')
            continue;
        root = add_node(word, 1, root);
    }
    insert_sorting(root);
    print_list(list_root);
    return 0;
}

void insert_sorting(struct tnode* root)
{
    if (root == NULL)
        return;
    else {
        insert_sorting(root->right);
        list_root = add_list_node(root, list_root, NULL);
        insert_sorting(root->left);
    }
}

void print_list(struct tlist* root)
{
    for (; root != NULL; root = root->next) {
        printf("%d %s\n", root->current->count, root->current->word);
    }
}

struct tnode* add_node(char* word, int count, struct tnode* root)
{
    struct tnode* talloc(void);

    if (root == NULL) {
        root = talloc();
        root->word = strdup(word);
        root->count = count;
        root->right = root->left = NULL;
        return root;
    }
    if (strcmp(word, root->word) == 0) {
        root->count += count;
    }

    else if (strcmp(word, root->word) > 0)
        root->left = add_node(word, count, root->left);
    else
        root->right = add_node(word, count, root->right);
    return root;
}

struct tlist* add_list_node(struct tnode* node, struct tlist* root, struct tlist* prev)
{
    struct tlist* tlalloc(void);
    if (root == NULL) {
        struct tlist* new = tlalloc();
        new->next = NULL;
        new->current = node;
        if (prev != NULL)
            prev->next = new;
        else
            return new;
    } else if (root->next == NULL) {
        if (node->count <= root->current->count) {
            struct tlist* new = tlalloc();
            new->next = NULL;
            new->current = node;
            root->next = new;
        } else {
            struct tlist* new = tlalloc();
            new->next = root;
            new->current = node;
            if (prev != NULL)
                prev->next = new;
            return new;
        }
    } else {
        if (node->count >= root->current->count) {
            struct tlist* new = tlalloc();
            new->next = root;
            new->current = node;
            if (prev != NULL)
                prev->next = new;
            else
                return new;
        } else {
            add_list_node(node, root->next, root);
        }
    }
    return root;
}

struct tlist* tlalloc(void)
{
    return (struct tlist*)malloc(sizeof(struct tlist));
}

struct tnode* talloc(void)
{
    return (struct tnode*)malloc(sizeof(struct tnode));
}

void print_pre_order(struct tnode* root)
{
    if (root == NULL)
        return;
    print_pre_order(root->left);
    printf("%d %s\n", root->count, root->word);
    print_pre_order(root->right);
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
