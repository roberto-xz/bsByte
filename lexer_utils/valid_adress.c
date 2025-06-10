
/*
 ** autor: roberto-xz 10, Junho 2025
 **
*/

#include <string.h>
#include <string.h>
#include <stdlib.h>

short valid_adress(char *adress) {
    if (adress == NULL) return 1;
    if (strlen(adress) < 7 || strlen(adress) > 7) return 1;

    // converter o hex para dec, e verificar se está no limite de intervalo
    // permitido.

    return 0;
}
