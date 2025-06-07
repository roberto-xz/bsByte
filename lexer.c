
//
// autor: roberto-xz 07, Junho 2025 
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/constants.h"
#include "structs/command_parts.h"
#include "utils.c"

int lexer(char *filename) {
    FILE *input_file = fopen(filename,"r");
    if (input_file == NULL ) {
        printf("lexer-error: file [%s] not found \n",filename);
        return 1;
    }

    char  lines[READ_CHAR_PER_LINE];
    int   lines_count = 1;
    short is_assigned = 0;
    
    while (fgets(lines,sizeof(lines),input_file) != NULL) {
        char *line = trim(lines); 
        if (lines_count == 1 ) {
            if (strlen(line) == 3 && strcmp(line,"_H_") == 0) is_assigned = 1;
            if (strlen(line) == 3 && strcmp(line,"_V_") == 0) is_assigned = 1;
            
            if (is_assigned == 0) {
                printf("lexer-error: file not assigned\n");
                return 1;
            }
        }
        
        
        lines_count +=1;
        command_parts parts = split_line(line);
        printf("%s",parts.part_1);
    }
    
    return 0;
}

int main() {
    lexer("exemplos/simple_sum.bs");
    return 0;
}
