#include <stdio.h>

#define LOWER 0
#define UPPER 100
#define STEP 10
main()
{
    int farh;
    for(farh = LOWER;farh <= UPPER; farh= farh + STEP)
    {
        printf("%3d\t%3.2f\n",farh, (farh - 32) * 5.0 / 9.0);
    }
}
