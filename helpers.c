/******************************************************************************
 * Student Name  : Matthew Ablott
 * MQ ID : 44649371
 * COMP202, Semester 1, 2017.
*****************************************************************************/
#include "helpers.h"
#include <stdlib.h>
#include <string.h>
/**
 * convenience function you may wish to use with strtok to create a temporary
 * string for tokenization.
 **/
char* strdup(const char orig[]) {
    /* make space for the new stringg */
    char* copy = malloc(sizeof(char) + (strlen(orig) + 1));
    if (copy == NULL) {
        return NULL;
    }
    /* copy the string */
    strcpy(copy, orig);
    return copy;
}
