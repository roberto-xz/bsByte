
/*
** autor: roberto-xz 07, Junho 2025
**
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer_utils/valid_adress.c"
#include "lexer_utils/valid_accum.c"
#include "lexer_utils/valid_stvalue.c"
#include "constants.h"
#include "utils.c"

/*
*
* função para analisar a primeira parte de uma instrução, (mnemónico)
* 1° verifica se possue 3 bytes, número máximo permitido
* 2° verifica se é um mnemónico válido. (Se pertence as palavras reservadas)
*/
int analize_part_1(char part_1[], int line) {
    if (strlen(part_1) < 3 || strlen(part_1) > 3 ) {
        printf("lexer-error: invalid mnemonio %s line: %d\n", part_1, line);
        return 1;
    }

    if (strstr(RESERVED_WORDS,part_1) == NULL) {
        printf("lexer-error: invalid mnemonio %s line: %d\n",part_1, line);
        return 1;
    }

    return 0;
}

/*
 *
 * função para analisar a segunda parte de uma instrução
 *
 * 1° verifica se é um jump.
 *      1° verifica o tipo de salto, endereço ou label
 *      2° verifica se existe o label
 *
 * 2° verifica se uma instrução mov, ou say
 *      1° verifica se o primerio argumento é um accumulator válido
 *      2° verifica se o primeiro argumento é um endereço válido
 *
 */
int analize_part_2(char part_1[], char part_2[], int line, char labels[20][20],int label_count) {
    if (strcmp(part_1,"jpm") == 0) {
        // verifica se é um endereço e se é válido
        if (part_2[0] == '#') {
            if (valid_adress(part_2)) {
                printf("lexer-error: invalid jump adress %s: line -> %d\n", part_2, line);
                return 1;
            }
        }
        // varifica se é um label e se é válido.
        if (part_2[0] == '$') {
            short label_is_declared = 0;
            for (int x=0; x<label_count; x++){
                if (strstr(labels[x],part_2)) label_is_declared = 1;
            }

            if (label_is_declared == 0 ) {
                printf("lexer-error: label %s not declared: line -> %d\n", part_2, line);
                return 1;
            }
        }
    }

    if (strcmp(part_1,"mov") == 0 || strcmp(part_1,"say") == 0 ) {
         // varifica se é um endereço e se é válido
        if (part_2[0] == '#') {
            if (valid_adress(part_2)) {
                printf("lexer-error: invalid jump adress %s: line -> %d\n", part_2, line);
                return 1;
            }
        }
    }

    // varifica se é um acumulador e se é válido
    if (part_2[0] == '@') {
        if (valid_accum(part_2)) {
            printf("lexer-error: invalid accumulator adress %s: line -> %d\n", part_2, line);
            return 1;
        }
    }
    return 0;
}


int analize_part_3(char part_1[], char part_3[], int line){
    if (strcmp(part_1,"jpm") == 0 || strcmp(part_1,"say") == 0) return 0;
    if (strcmp(part_1,"mov") == 0 ) {
        if (part_3[0] == '#'){
            if (valid_adress(part_3)) {
                printf("lexer-error: invalid adress %s: line -> %d\n", part_3, line);
                return 1;
            }
        }
        if (part_3[0] == '@'){
            if (valid_accum(part_3)) {
                printf("lexer-error: invalid accumulator adress %s: line -> %d\n", part_3, line);
                return 1;
            }
        }
    }

    if (strcmp(part_1,"set") == 0) {
        if (valid_stvalue(part_3)) {
            printf("lexer-error: invalid hex(6) value %s: line -> %d\n", part_3, line);
            return 1;
        }
    }

    if (part_3[0] == '#') {
        if (valid_adress(part_3)) {
            printf("lexer-error: invalid jump adress %s: line -> %d\n", part_3, line);
            return 1;
        }
    }

    return 0;
}

int lexer(char* filename) {
    FILE* file_data = fopen(filename, "r");
    if (file_data == NULL) {
        printf("lexer-error: file [%s] not found \n", filename);
        return 1;
    }

    char buffer[READ_CHAR_PER_LINE];
    char labels[20][20];

    int label_count = 0;
    int lines_count = 1;
    int is_assigned = 0;

    while (fgets(buffer, sizeof(buffer), file_data) != NULL) {
        char* line = trim(buffer);

        // verifica se há uma assinatura no arquivo
        if (lines_count == 1) {
            if (strlen(line) == 3 && strcmp(line, "_H_") == 0) is_assigned = 1;
            if (strlen(line) == 3 && strcmp(line, "_V_") == 0) is_assigned = 1;

            if (is_assigned == 0) {
                printf("lexer-error: file not assigned\n");
                return 1;
            }
        }

        if (strlen(line) >= 3 && line[0] != ';' && lines_count > 1) {
            if (line[0] == ':') {
                strncpy(labels[label_count], strtok(line, " "), 19);
                labels[label_count][19] = '\0';
                labels[label_count][0] = '$';
                label_count +=1;
            }else {
                command_parts cmd_parts = split_line(line);
                if (analize_part_1(cmd_parts.part_1, lines_count) == 1) {return 1;}
                if (analize_part_2(cmd_parts.part_1,cmd_parts.part_2, lines_count,labels,label_count) == 1){return 1;}
                //if (analize_part_3(cmd_parts.part_1, cmd_parts.part_3,lines_count) == 1) return 1;
            }
        }
        lines_count += 1;
    }

    return 0;
}



int main() {
    lexer("exemplos/simple_sum.bs");

    return 0;
}
