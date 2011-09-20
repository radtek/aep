#include "massert.h"
#include <stdio.h>

void AssertFail(const char *file, int line, const char *function, const char *cond)
{
    printf("%s: MASSERT(%s) failed at %s line %d\n", function, cond, file, line);
    fflush(stdout);
}
