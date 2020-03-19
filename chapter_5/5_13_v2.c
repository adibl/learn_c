/* 
 * spare computation power because the input is directly moved to the array
 * and don't need to be copied secound time 
 * vedion 2 use bildin getline to alocate memeory automaticly and spare memory use + make it faster 
 * becuse bildin getline id faster
 * */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000


int atoi(const char *str);

int main(int argc, char *argv[])
{
    int n = 10;
    ++argv;
    if (argc > 1) {
        if (*argv[0] == '-') {
            n = -1 * atoi(*argv);

        } else
            fprintf(stderr, "no argument option %s\n", *argv);

    }

    n++;
    char *tail[n];
    int len, i;
    i = 0;
    size_t size = 0;
    int is_first_round = 1;
    while ((len = getline(&tail[i], &size, stdin)) > 0) {
        if (i < n - 1)
            i++;
        else {
            i = 0;
            is_first_round = 0;
        }
        if (is_first_round != 1)
            free(tail[i]);
        size = 0;
    }
    free(tail[i]);
    int boundery_i = i;
    if (i < n - 1)
        i++;
    else
        i = 0;
    for (; i < n; i++) {
        printf("%s", tail[i]);
        free(tail[i]);
    }
    for (i = 0; i < boundery_i; i++) {
        printf("%s", tail[i]);
        free(tail[i]);
    }
    return 0;

}
