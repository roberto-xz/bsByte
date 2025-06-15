
/*
 ** stack de erros
 ** autor: roberto-xz 15, Junho 2025
 */

#include "structs/error.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define COLOR_MODULE "\033[96m"
#define COLOR_ERROR  "\033[91m"
#define COLOR_LINE   "\033[93m"
#define COLOR_RESET  "\033[0m"
struct _error_node *erro_top = NULL;


void add_error(char *_module, char *_error, char *_descr, short  _line) {
    struct _error_node *n_error_node = malloc(sizeof(struct _error_node));
    strcpy(n_error_node->_module,_module);
    strcpy(n_error_node->_error,_error);
    strcpy(n_error_node->_descr,_descr);
    n_error_node->_line = _line;
    n_error_node->next_node = erro_top;
    erro_top = n_error_node;
}

short print_erros() {
    struct _error_node *aux = erro_top;
    short erros = 0;

    while (aux != NULL) {
        printf(COLOR_MODULE "[%s]" COLOR_RESET " ", aux->_module);
        printf(COLOR_ERROR "%s" COLOR_RESET " ", aux->_error);
        printf(COLOR_LINE "at line %02d:" COLOR_RESET " ", aux->_line);
        printf("%s\n", aux->_descr);

        aux = aux->next_node;
        erros +=1;
    }

    return erros;
}

