
//
// autor: roberto-xz 07, Junho 2025 
//

#include <stdint.h>
#include "constants.h"

struct opcode {
    uint32_t _opcode: OP_BITS; 
    uint32_t _accumu: AC_BITS; 
    uint32_t _adress: AD_BITS; 
}
