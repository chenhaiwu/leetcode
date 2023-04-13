#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>


bool FindNextCity(char *** paths, int pathsSize, char *from)
{
    bool ret = false;
    for (int i = 0; i < pathsSize; i++) {
        char *dest = paths[i][0];
        if (strcmp(dest, from) == 0) {
            return true;
        }
    }
    return ret;
}

char * destCity(char *** paths, int pathsSize, int* pathsColSize)
{
    for (int i = 0; i < pathsSize; i++) {
        char *from = paths[i][1];
        if (!FindNextCity(paths, pathsSize, from)) {
            return from;
        }
    }
    return NULL;
}