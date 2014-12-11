#ifndef _DISASM_CODE_H
#define _DISASM_CODE_H

#include <stdint.h>
#include "fonction_base.h"
#include "fonction_token.h"
#include "fonction_mem.h"
#include "elf/syms.h"

#define MAX_NOM 64

typedef struct {
  uint32_t signature;
  uint32_t masque;
  char nom[MAX_NOM];
  char type;
  char * op_mapping[MAX_NOM];
  int nmbr_oper;
  int num_function;
} *definition;


typedef struct {
	unsigned int function : 6;
	unsigned int sa : 5;
	unsigned int rd : 5;
	unsigned int rt : 5;
	unsigned int rs : 5;
	unsigned int opcode : 6;

}R;

typedef struct {
	int immediate : 16;
	unsigned int rt : 5;
	unsigned int rs : 5;
	unsigned int opcode : 6;

}I;


typedef struct {
	unsigned int target : 26;
	unsigned int opcode : 6;
}J;

typedef struct {
	 R r;
	 I i;
	 J j;
}union_RIJ;

enum{CMD_DISASM_OK_PLAGE,CMD_DISASM_OK_DECALAGE,ADRS_NON_HEXA3,MAUVAIS_DECALAGE,ERREUR_SYNTAXE,POSITION_IMPOSSIBLE,PAS_ADRESSE,HORS_ZONE_TEXTE,TOO_MUCH};

int test_cmd_disasm(interpreteur inter, uint32_t * adr1, uint32_t * adr2,int * decalage);
int cmd_disasm(interpreteur inter,mem  memoire,map_reg * mrg,stab  symtab);
definition lecture_dictionnaire(char * file_name);
void erreur_fonction_disasm(int verification);
int execute_cmd_disasm( uint32_t adr1 , uint32_t adr2 , int decalage, int decalage_plage,mem memoire,map_reg * mrg,stab  symtab);
union_RIJ return_operande(char type_struct,uint32_t mot);




#endif