#ifndef _FONCTION_MEM_H
#define _FONCTION_MEM_H

#include "fonction_base.h"
#include "registre.h"


void affiche_mot (mem virtualm, uint32_t vaddr1);
uint32_t renvoi_mot (mem virtualm, uint32_t vaddr1,map_reg * mrg);
uint8_t renvoi_byte (mem virtualm, uint32_t vaddr1,map_reg * mrg);
int set_byte (mem virtualm, uint32_t vaddr1,uint8_t byte,map_reg * mrg);


#endif