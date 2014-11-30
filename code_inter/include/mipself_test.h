#ifndef mipself_test_h
#define mipself_test_h

#include <stdio.h>
#include <stdlib.h>
#include "common/bits.h"
#include "common/notify.h"
#include "elf/elf.h"
#include "elf/syms.h"
#include "mem.h"


// On fixe ici une adresse basse dans la mémoire virtuelle. Le premier segment
// ira se loger à cette adresse.
#define START_MEM 0x5000
// nombre max de sections que l'on extraira du fichier ELF
#define NB_SECTIONS 8

//nom du prefix ‡ appliquer pour la section
#define RELOC_PREFIX_STR ".rel"

// nom de chaque section
#define TEXT_SECTION_STR ".text"
#define RODATA_SECTION_STR ".rodata"
#define DATA_SECTION_STR ".data"
#define BSS_SECTION_STR ".bss"
#define HEAP_SECTION_STR "[heap]"
#define LIB_SECTION_STR "[lib]"
#define STACK_SECTION_STR "[stack]"
#define VSYSCALL_SECTION_STR "[vsyscall]"


int is_in_symbols(char* name, stab symtab);
unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections);
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start);
void print_segment_raw_content(segment* seg);




#endif