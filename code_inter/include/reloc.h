#ifndef reloc_h
#define reloc_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common/bits.h"
#include "common/notify.h"
#include "elf/elf.h"
#include "elf/syms.h"
#include "elf/relocator.h"
#include "mem.h"
#include "mipself_test.h" 
#include "registre.h"
#include "fonction_mem.h"

void reloc_segment(FILE* fp, segment seg, mem memory,unsigned int endianness,stab symtab,map_reg * mrg);


#endif