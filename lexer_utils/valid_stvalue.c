
/*
 * * autor: roberto-xz 10, Junho 2025
 **
*/

#include <string.h>
#include <stdlib.h>

short valid_stvalue(char *value) {
    if (value == NULL) return 1;
    if (strlen(value) != 6 ) return 1;

    unsigned int hex_val = (unsigned int) strtol(value, NULL, 16);
    if (hex_val > 0x1FFFF) return 1;

    int sign_bit = (hex_val & (1 << 16)) != 0;
    int signed_val = sign_bit ? hex_val - (1 << 17) : hex_val;

    if (signed_val < -65536 || signed_val > 65535) return 1;

    return 0;
}
