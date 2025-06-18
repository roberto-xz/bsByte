
/*
 ** token node
 ** autor: roberto-xz 18, Junho 2025
 */


struct token_node {
    char *token;
    char *value;
    int    line;

    struct token_node *nex_node;
};
