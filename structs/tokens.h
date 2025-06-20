
/*
 ** token node
 ** autor: roberto-xz 18, Junho 2025
 */


struct token_node {
    char token[300];
    char value[50];

    int    line;
    int    coll;
    struct token_node *nex_node;
};
