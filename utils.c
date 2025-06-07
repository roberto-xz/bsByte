
//
// autor: roberto-xz 07, Junho 2025 
//

#include <ctype.h>
#include <string.h>
#include "./structs/command_parts.h"

char *trim (char *str) {
    if (*str == 0 ) return str; // caso a string seja vazia
    while (isspace((unsigned char)*str)) { str++; } // incrementa o ponteiro sempre que encontrar um espaço em branco
    
    // calucula o endereço final da string
    char *end = str + strlen(str) - 1;

    while (end > str && isspace((unsigned char)*end)) {
        // enquanto for um espaço, decrementa o endereço final
        end--;
    }
    *(end + 1) = 0;
    return str;
}

command_parts split_line(char *str) {
    command_parts parts;
    parts.part_1 = "lda";
    parts.part_2 = "@1";
    parts.part_3 = "#0x0111";
    return parts;
}


