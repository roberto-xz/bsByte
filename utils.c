
//
// autor: roberto-xz 07, Junho 2025
//

#include "./structs/command_parts.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char* trim(char* str) {
    if (*str == 0) return str; // caso a string seja vazia

    // incrementa o ponteiro sempre que encontrar um espaço em branco
    while (isspace((unsigned char)*str)) { str++;}

    // calucula o endereço final da string
    char* end = str + strlen(str) - 1;

    // enquanto for um espaço, decrementa o endereço final
    while (end > str && isspace((unsigned char)*end)) { end--;}
    *(end + 1) = 0;
    return str;
}

command_parts split_line(char* str) {
    command_parts parts;
    parts.part_1 = strtok(str, " ");
    parts.part_2 = strtok(NULL," ");
    parts.part_3 = strtok(NULL," ");
    return parts;
}
