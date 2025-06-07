
//
// stack principal do runtime
// autor: roberto-xz 07, Junho 2025 
//

#include "opcode.h"

struct stack_opcodes {
    struct stack_opcodes *next;
    struct opcode _op;
}
