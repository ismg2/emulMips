#include "common/bits.h"
#include "common/notify.h"
#include "elf/elf.h"
#include "elf/syms.h"


#ifndef _REGISTRE_H_
#define _REGISTRE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


typedef uint32_t reg;

typedef struct {char* mnemonique, int numero, int* pointeur} * map_reg;










#ifdef __cplusplus
}
#endif

#endif
