//#include "common/bits.h"
#include "common/notify.h"
//#include "elf/elf.h"


#ifndef _REGISTRE_H_
#define _REGISTRE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdio.h>

//typedef uint32_t reg

typedef struct {char* mnemonique; int numero; int * pointeur;} *map_reg;

map_reg remplir_registre(char* mnemo, int num, int val);
map_reg * creer_map_reg();
void suppr_reg (map_reg rm, int num);
void affiche_reg (int indic, int origine, int fin, map_reg rm);
void copier_reg_reg_via_num (map_reg rm, int num_src, int num_dest);
int renvoi_reg_num (map_reg rm, int num);
void modif_reg_num (int num, map_reg rm, int contenu);
int convert_dollarnum_num(map_reg rm, char* dollarnum);
void modif_reg_dollarnum (char* dollarnum, map_reg rm, int contenu);
int renvoi_reg_dollarnum (map_reg rm, char* dollarnum);
void copier_reg_reg_via_dollarnum (map_reg rm, char* dollarnum_src, char* dollarnum_dest);
int convert_mnemo_num(map_reg rm, char* mnemo);
void modif_reg_mnemo (char* mnemo, map_reg rm, int contenu);
int renvoi_reg_mnemo (map_reg rm, char* mnemo);
void copier_reg_reg_via_mnemo (map_reg rm, char* mnemo_src, char* mnemo_dest);
char* convert_num_mnemonique(map_reg rm, int num);


#ifdef __cplusplus
}
#endif

#endif
