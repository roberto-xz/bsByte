
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
#include "error.c"
#include "utils.c"
#include "tokens.c"



void analize_part_1(char part_1[], int line) {
    if (strlen(part_1) != 3  || strstr(RESERVED_WORDS,part_1) == NULL)
        add_error("lexer","sintax error","invalid mnemonio",line);
}

void analize_part_2(command_parts command, int line) {
    if (strcmp(command.part_1,"jpm") == 0) {
        if (command.part_2[0] == '#')
            if (valid_adress(command.part_2)) add_error("lexer","jump","invalid jump adress",line);
        if (command.part_2[0] == '$'){/*validar os labels*/}
    }

    if (strcmp(command.part_1,"mov") == 0 || strcmp(command.part_1,"say") == 0)
        if (command.part_2[0] == '#') {
            if (valid_adress(command.part_2)) add_error("lexer","jump","invalid jump adress",line);
        }

    if (command.part_2[0] == '@')
        if (valid_accum(command.part_2)) add_error("lexer","accumulator","invalid accumulator",line);
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
    struct token_node *tokens = NULL;

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

        if (lines_count == 1) {
            if (strlen(line) == 3 && strcmp(line, "_H_") == 0) is_assigned = 1;
            if (strlen(line) == 3 && strcmp(line, "_V_") == 0) is_assigned = 1;
            if (is_assigned == 0)
                add_error("lexer","file type","file not assigned",0);
        }

        if (strlen(line) >= 3 && line[0] != ';' && lines_count > 1) {
            command_parts cmd_parts = split_line(line);
            add_token(cmd_parts.part_1,lines_count,1,&tokens);

            if (strcmp(cmd_parts.part_1, "ext") != 0) {
                add_token(cmd_parts.part_2, lines_count, 2, &tokens);
                if (strcmp(cmd_parts.part_1, "say") != 0 && strcmp(cmd_parts.part_1, "jpm") != 0)
                    add_token(cmd_parts.part_3, lines_count, 3, &tokens);
            }
        }

        lines_count += 1;
    }
    print_tokens(&tokens);
    return 0;
}



int main() {
    lexer("exemplos/simple_sum.bs");

    return 0;
}
