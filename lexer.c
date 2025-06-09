
/*
** autor: roberto-xz 07, Junho 2025
**
*/

#include "constants.h"
#include "utils.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*
* função para analisar a primeira parte de uma instrução, (mnemónico)
* 1° verifica se possue 3 bytes, número máximo permitido
* 2° verifica se é um mnemónico válido.
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
 */
int analize_part_2(char part_1[], char part_2[], int line, char labels[20][20],int label_count) {
    if (strcmp(part_1,"jpm") == 0) {
        if (part_2[0] == '#') {
            if (strlen(part_2) < 6 || strlen(part_2) > 6 ) {
                printf("lexer-error: invalid jump adress %s: line -> %d\n", part_2, line);
                return 1;
            }
        }

        if (part_2[0] == '$') {
            short label_is_declared = 0;
            for (int x=0; x<label_count; x++)
                if (strstr(labels[x],part_2)) label_is_declared = 1;

            if (label_is_declared == 0 ) {
                printf("lexer-error: label %s not declared: line -> %d\n", part_2, line);
                return 1;
            }
        }
    }

    if (strcmp(part_1,"mov") == 0 || strcmp(part_1,"say") == 0 ) {
        if (part_2[0] == '@') {} // registrador
        if (part_2[0] == '#') {} // endereço
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
                label_count +=1;
            }else {
                command_parts cmd_parts = split_line(line);
                if (analize_part_1(cmd_parts.part_1, lines_count) == 1) return 1;
                if (analize_part_2(cmd_parts.part_1,cmd_parts.part_2, lines_count,labels,label_count) == 1) return 1;
                // break;
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
