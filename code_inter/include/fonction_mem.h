#ifndef _FONCTION_MEM_H
#define _FONCTION_MEM_H

#include "fonction_base.h"
#include "registre.h"

#define byte1 0xFF
#define byte2 0xFF00
#define byte3 0xFF0000
#define byte4 0xFF000000

void affiche_mot (mem virtualm, uint32_t vaddr1);
uint32_t renvoi_mot (mem virtualm, uint32_t vaddr1,map_reg * mrg);
uint8_t renvoi_byte (mem virtualm, uint32_t vaddr1,map_reg * mrg);
int set_byte (mem virtualm, uint32_t vaddr1,uint8_t byte,map_reg * mrg);
int set_word(mem virtualm, uint32_t vaddr1,uint32_t word,map_reg * mrg);
void affiche_byte (mem virtualm, uint32_t vaddr1);
#endif