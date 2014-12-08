#ifndef _set_h
#define _set_h


#include "fonction_token.h"
#include "get_type_token.h"
#include "fonction_mem.h"
#include "registre.h"

enum {CMD_SET_REG_OK,CMD_SET_WORD_OK,CMD_SET_BYTE_OK,NO_TYPE_VALUE,PAS_VALEUR_A_TESTER,ADRS_NON_HEXA2,REGI_NON_EXISTANT,ERROR_i,CMD_SET_UK,PAS_DADRESSE_ENTREE2};
int execute_set_word(char * adr,char * val,mem memoire,map_reg * mrg);
int execute_set_byte(char * adr,char * val,mem memoire,map_reg * mrg);
int execute_set_reg(char * reg1,char * value, map_reg * mrg,int position_reg);
int test_cmd_set(interpreteur inter,char * wb,char ** value,char ** adr);
void erreur_cmd_set(int verif);
int test_cmd_set_reg(interpreteur inter,char ** tab_tout_reg,char * reg1,char ** value,int * position);
int cmd_set(interpreteur inter,mem memoire,map_reg * mrg); 


#endif