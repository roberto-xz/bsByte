
/*
** autor: roberto-xz 07, Junho 2025
**
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.c"
#include "tokens.c"

short lexer(char* filename,  struct token_node **tokens) {
    FILE* file_data = fopen(filename, "r");
    char buffer[1024];

    if (file_data == NULL) {
        printf("lexer-error: file [%s] not found \n", filename);
        return 1;
    }

    int lines_count = 1;
    int is_assigned = 0;

    while (fgets(buffer, sizeof(buffer), file_data) != NULL) {
        char* line_buffer = trim(buffer);

        if (lines_count == 1) {
            if (strlen(line_buffer) == 3 && strcmp(line_buffer, "_H_") == 0) is_assigned = 1;
            if (strlen(line_buffer) == 3 && strcmp(line_buffer, "_V_") == 0) is_assigned = 1;
            if (is_assigned == 0) return 2;
        }

        if (strlen(line_buffer) >= 3 && line_buffer[0] != ';' && lines_count > 1) {
            command_parts cmd_parts = split_line(line_buffer);
            add_token(cmd_parts.part_1,lines_count,1,tokens);

            if (strcmp(cmd_parts.part_1, "ext") != 0) {
                add_token(cmd_parts.part_2, lines_count, 2,tokens);
                if (strcmp(cmd_parts.part_1, "say") != 0 && strcmp(cmd_parts.part_1, "jpm") != 0)
                    add_token(cmd_parts.part_3, lines_count, 3,tokens);
            }
        }

        lines_count++;
    }
    fclose(file_data);
    return 0;
}

