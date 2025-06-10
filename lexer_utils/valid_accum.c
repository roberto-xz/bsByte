
/*
 ** autor: roberto-xz 10, Junho 2025
 **
*/

#include <string.h>
#include <string.h>
#include <stdlib.h>

short valid_accum(char *acm) {
    if (acm ==   NULL) return 1;
    if (strlen(acm) > 2 || strlen(acm) < 2 ) return 1;

    char ac_value[2] = {acm[1],'\0'};
    if (atoi(ac_value) < 0 || atoi(ac_value) > 4 ) return 1;

    return 0;
}
