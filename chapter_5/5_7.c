#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           /* max #lines to be sorted */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char lines_array[]);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
/* sort input lines */
main()
{
    int nlines;
    char lines_array[MAXLINES*100];
/* number of input lines read */
    if ((nlines = readlines(lineptr, MAXLINES, lines_array)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000             /* max length of any input line */
int getline2(char *, int);
void *malloc(size_t);
/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char lines_array[])
{
    int len, nlines;
    char *p, line[MAXLEN];
    p = lines_array;
    nlines = 0;
    while ((len = getline2(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            line[len - 1] = '\0';       /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len + 1;
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

/* qsort: sort v[left]...v[right] into increasing order */
void swap(char *v[], int i, int j);

void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)          /* do nothing if array contains */
        return;
/* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
