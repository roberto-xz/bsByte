
//
// struct para representar os dois tipos de arquitetura de gerenciamento de memória
// suportados por o linguagem. Havard e Von Neuman
//
// autor: roberto-xz 07, Junho 2025
//

#include "constants.h"

struct memory {
    char memory_type;
    char slot_a[MAX_MEMORY];
    char slot_b[MAX_MEMORY];
}
