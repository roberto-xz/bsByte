
/*
 ** autor: roberto-xz 10, Junho 2025
 **
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

short valid_adress(char *adress) {
    if (adress == NULL) return 1;
    if (strlen(adress) != 7) return 1;

    unsigned int hex_val = (unsigned int) strtol(adress + 1, NULL, 16);
    if (hex_val > 0x1FFFF) return 1;

    if (hex_val & (1 << 16)) return 1; // rejeita negativos

    return 0;
}
