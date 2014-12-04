#ifndef _fonction_assert_h
#define _fonction_assert_h

#include "fonction_token.h"
#include "get_type_token.h"
#include "fonction_mem.h"
#include "registre.h"

enum {CMD_ASSERT_REG_OK,CMD_ASSERT_WORD_OK,CMD_ASSERT_BYTE_OK,NO_TYPE_VALUE,PAS_VALEUR_A_TESTER,ADRS_NON_HEXA2,REGI_NON_EXISTANT,ERROR_i};

int execute_assert_word(char * adr,char * val,mem memoire);
int execute_assert_byte(char * adr,char * val,mem memoire);
int execute_assert_reg(char * reg1,char * value, map_reg * mrg,int position_reg);
int test_cmd_assert(interpreteur inter,char * wb,char ** value,char ** adr);
void erreur_cmd_assert(int verif);
int test_cmd_assert_reg(interpreteur inter,char ** tab_tout_reg,char * reg1,char ** value,int * position);
int cmd_assert(interpreteur inter,mem memoire,map_reg * mrg); 

#endif
