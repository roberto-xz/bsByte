
/*
 ** pilha de tokens
 ** autor: roberto-xz 18, Junho 2025
 */

#include "structs/tokens.h"
#include "structs/command_parts.h"
#include "constants.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct token_node *tokens_head = NULL;


void add_token(char *buffer, int line, int part) {
    struct token_node *n_token_node = malloc(sizeof(struct token_node));

    if (strstr(RESERVED_WORDS,buffer) && part == 1) {
        if (strcmp(buffer,"ext")== 0) strcpy(n_token_node->token,"EXIT_METHOD");
        if (strcmp(buffer,"lda")== 0) strcpy(n_token_node->token,"LOAD_METHOD");
        if (strcmp(buffer,"sta")== 0) strcpy(n_token_node->token,"STORAGE_METHOD");
        if (strcmp(buffer,"sum")== 0) strcpy(n_token_node->token,"SUM_METHOD");
        if (strcmp(buffer,"sub")== 0) strcpy(n_token_node->token,"SUBTRATION_METHOD");
        if (strcmp(buffer,"div")== 0) strcpy(n_token_node->token,"DIVISION_METHOD");
        if (strcmp(buffer,"mov")== 0) strcpy(n_token_node->token,"MOVE_METHOD");
        if (strcmp(buffer,"set")== 0) strcpy(n_token_node->token,"SET_METHOD");
        if (strcmp(buffer,"say")== 0) strcpy(n_token_node->token,"PRINT_METHOD");
        if (strcmp(buffer,"jpm")== 0) strcpy(n_token_node->token,"INCONDITION_JUMP_METHOD");
        if (strcmp(buffer,"jpz")== 0) strcpy(n_token_node->token,"JUMP_IF_ACM_0_METHOD");
        if (strcmp(buffer,"jpn")== 0) strcpy(n_token_node->token,"JUMP_IF_ACM_NEGATIVE_METHOD");
        if (strcmp(buffer,"and")== 0) strcpy(n_token_node->token,"AND_OPERATION");
        if (strcmp(buffer,"not")== 0) strcpy(n_token_node->token,"NOT_OPERATION");

        n_token_node->line = line;
        n_token_node->coll = 1;
        strcpy(n_token_node->value, buffer);
        n_token_node->nex_node = tokens_head;
        tokens_head = n_token_node;
        return;
    }

    if (part == 2 || part == 3) {
        if (buffer[0] == '@') strcpy(n_token_node->token,"ACCUMULATION_OPERAND");
        if (buffer[0] == '#') strcpy(n_token_node->token,"HEX_VALUE_OPERAND");
        if (buffer[0] == '$') strcpy(n_token_node->token,"TEXT_VALUE_OPERAND");
        if (buffer[0] == '%') strcpy(n_token_node->token,"DECIMAL_VALUE_OPERAND");

        n_token_node->line = line;
        n_token_node->coll = 1;
        strcpy(n_token_node->value, buffer);
        n_token_node->nex_node = tokens_head;
        tokens_head = n_token_node;
        return;
    }
    return;
}

short print_tokens() {
    struct token_node *aux = tokens_head;
    short tokens = 0;

    while (aux != NULL) {
        printf("%s -> %d:%d\n",aux->token,aux->line,aux->coll);
        aux = aux->nex_node;
        tokens +=1;
    }
    return tokens;
}




