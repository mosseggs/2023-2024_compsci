#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
#define LIM 4000000
    char p[LIM + 1];    /* +1 for terminating null byte */
    time_t base;

    base = time(NULL);
    p[0] = '\0';

    for (int j = 0; j < LIM; j++) {
        if ((j % 10000) == 0)
            printf("%d %jd\n", j, (intmax_t) (time(NULL) - base));
        strcat(p, "a");
        printf("%s\n",p);
    }
}