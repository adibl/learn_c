#include <stdio.h>
#include <limits.h>
#include <float.h>

main()
{
    printf("char min %d max %d unsinded %u\n", SCHAR_MIN, SCHAR_MAX, UCHAR_MAX);
    printf("short min %d max %d unsined %u\n", SHRT_MIN, SHRT_MAX, USHRT_MAX);
    printf("int min %d max %d undinded max %u\n", INT_MIN, INT_MAX, UINT_MAX);
    printf("long min %ld max %ld unsined max %lu\n", LONG_MIN, LONG_MAX, ULONG_MAX);
    signed char c, before;
    unsigned char uc ,ubefore;
    c = 0;
    before = -1; 
    while (c > before) {
        before = c;
        ++c;
    }
    uc = 1;
    ubefore = 0;
    while (uc > ubefore){
        ubefore = uc;
        ++uc;
    }
    printf("char min %d max %d unsined max %u\n", before, c, ubefore);
    signed short s, s_before;
    unsigned short u_s, u_before;
    s = u_s = 1;
    s_before = u_before = 0;
    while (s > s_before){
        s_before = s;
        ++s;
    }
    while (u_s > u_before){
        u_before = u_s;
        ++u_s;
    }
    printf("short min %d max %d unsined max %d\n", s_before, s , u_before);
    signed int i , i_before;
    unsigned int u_i, u_ibefore;
    i = u_i = 1;
    i_before = u_ibefore = 0;
    while (i > i_before){
        ++i_before;
        ++i;
    }
    while (u_i > u_ibefore){
        ++u_ibefore;
        ++u_i;
    }
    printf("int min %d max %d unsined max %u\n", i, i_before, u_ibefore);
    signed long l, l_before;
    signed long u_l, u_lbefore;
    l = u_l = 2;
    l_before = u_lbefore = 1;
    int div, div_max, div_jump;
    div_max = 1000000000;
    div_jump = 10;
    for (div = 1; div < div_max; div = div + div_jump) {
        while (l > l_before){
            l_before = l;
            l = l / div * div_max;
        }
        l = l_before;
        l_before = l / div_max * div;
    }
    l_before = l - 1;
    while (l > l_before){
        ++l_before;
        ++l;
    }
    printf("long min %ld max %ld\n", l, l_before);
}

