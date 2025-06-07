
//
// instruções suportadas por a linguagem
// autor: roberto-xz 07, Junho 2025 
//
//

// sintax de baixo nível, 24 bits por instrução
// +-------------------------------------------+
// | opcode  | accumulator | operand/argument  |
// |---------+-------------+-------------------+
// | 00000   | 00          | 00000000000000000 |
// +-------------------------------------------+

// sintax com mnemónicos 
// +-------------------------------------------+
// | opcode | mnemónico | sintax               |
// +--------+-----------+----------------------+
// | 00001  | ext       | ext                  |
// | 00011  | lda       | lda @1 #adress       |
// | 00111  | sta       | sta @1 #adress       |
// | 01111  | sum       | sum @1 #adress       |
// | 11111  | sub       | sub @1 #adress       |
// | 10001  | div       | div @1 #adress       |
// | 11001  | jmp       | jpm #adress/$label   |
// | 11101  | jpz       | jpz @1 #adress       |
// | 01101  | jpn       | jpn @1 #adress       |
// | 01010  | and       | and @1 #adress       |
// | 00101  | not       | not @1 #adress       |
// | 01001  | mov       | mov @# @#            |
// | 10000  | set       | set @1 value         |
// | 00000  | say       | say @#               |
// +-------------------------------------------+
//

#include "../memory.h"
#include "../accumulators.h"

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
    void ext(); // termina o programa
    void lda(accumulators *a, memory *m, int adress, int acm); // carrega o valor do endereço, no acumulador 
    void sta(accumulators *a, memory *m, int adress, int acm); // salva um valor do acumulador no endereço
    void add(accumulators *a, memory *m, int adress, int acm); // soma valor do endereço no acumulador
    void sub(accumulators *a, memory *m, int adress, int acm); // subtrai do acumulador o valor do endereço
    void div(accumulators *a, memory *m, int adress, int acm); // divide o valor do acumulador por o do endereço e salva no acumulador
    void jmp(int *prog_count, int adress); // realiza um salto incondicional
    void jpz(accumulators *a, int *prog_count, int adress, int acm); // faz um jump para o endereço, caso o acumulador seja 0
    void jpn(accumulators *a, int *prog_count, int adress, int acm); // faz um jump para o endereço, caso o acumulador seja negativo
    void _and(accumulators *a, memory *m, int adress, int acm); // realiza uma operação and, e salva no acumulador
    void _not(accumulators *a, memory *m, int adress, int acm); // realiza uma operação not, e salva no acumulador
    void mov(accumulators *a, memory *m, int adress, int acm, int src, int dst); // move os valores entre acumuladores e memoria
    void set(accumulators *a, int acm, int value); // atribue um valor diretamente a um acumulador
    void say(accumulators *a, memory *m, int acm, int adress);  // print o valor de um acmulador ou endereço
#endif
