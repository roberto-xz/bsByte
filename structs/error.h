
/*
** error node
** autor: roberto-xz 15, Junho 2025
*/

#include <string.h>
struct _error_node {
    char _module[20];  //modulo do erro [lexer, parser, runtime]
    char _error[80];   //erro, sintax erro, not declared, etc..
    char _descr[150];  //descrição do erro, mmnomio not found, etc..
    short  _line;      //linha

    struct _error_node *next_node;
};

