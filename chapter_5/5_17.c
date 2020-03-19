#include <stdio.h>
#include <string.h>
#define MAXLINES 5000
char *lineptr[MAXLINES];

int strcmp(const char *, const char *);

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *lineptr[], int left, int right,
            int (*comp) (void *, void *));
int numcmp(const char *, const char *);
int strcmpf(char *,char *);
int getline2(char s[], int lim);
void reverse(void *s[], int len);

int dir_order = 0, fold = 0;

int main(int argc, char *argv[])
{
    int nlines;
/* number of input lines read */
    int numeric = 0, arg_reverse = 0;
/* 1 if numeric sort */
    int (*function)(void *, void *) = strcmp;
    for (argv++, argc--; argc > 0; argv++, argc--) {
        if (strcmp(*argv, "-n") == 0)
            numeric = 1;
        else if (strcmp(*argv, "-r") == 0)
            arg_reverse = 1;
        else if (strcmp(*argv, "-f") == 0)
            fold = 1;
        else if (strcmp(*argv, "-d") == 0)
            dir_order = 1;
        else
            printf("unnowen option %s\n", *argv);
    }
    if (fold == 1 && numeric == 1) {
        printf("cant use -f and -n together, ignore -f\n");
        fold = 0;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric)
            function = numcmp;
        if (fold || dir_order)
            function = strcmpf;
        qsort2((void **) lineptr, 0, nlines - 1,
               (int (*)(void *, void *)) (function));
        if (arg_reverse)
            reverse((void **)lineptr, nlines);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void qsort2(void *v[], int left, int right, int (*comp) (void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right)
/* do nothing if array contains */
        return;
/* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp) (v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort2(v, left, last - 1, comp);
    qsort2(v, last + 1, right, comp);
}

#include <stdlib.h>

int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* readlines: read input lines */
#define MAXLEN 1000
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getline2(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';       /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int getline2(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

void reverse(void *s[], int len)
{
    void swap(void *v[], int, int);
    int low = 0, high = len - 1;
    for (; high >= low; low++, high--)
        swap(s, low, high);
}

int strcmpf(char *str1,char *str2)
{
    char *p = str1, *p2 = str2;
    char c1,c2;
    void fold_capital(char *c);
    char *next_dir_char(char *c);
        if (dir_order) {
            p = next_dir_char(p);
            p2 = next_dir_char(p2);
        }
    while (*p != '\0' && *p2 != '\0') {
        c1 = *p;
        c2 = *p2;
        if (fold == 1) {
            fold_capital(&c1);
            fold_capital(&c2);
        }
        if (c1 != c2)
            return c1 - c2;
        p++, p2++;
        if (dir_order) {
            p = next_dir_char(p);
            p2 = next_dir_char(p2);
        }
    }
    return (*p2 == '\0') - (*p == '\0');
}

void fold_capital(char *c)
{
    if (*c >= 'A' && *c <= 'Z')
        *c += 'a' - 'A';
}

char *next_dir_char(char *c) {
            while (!isdigit(*c) && !isalpha(*c) && !isspace(*c)) {
                if (*c == '\0')
                    return c;
                c++;
            }
            return c;
}
