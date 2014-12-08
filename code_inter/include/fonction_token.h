#ifndef _fonction_token_h
#define _fonction_token_h

#include "fonction_base.h"
#include "get_type_token.h"
#include <ctype.h>
#include "registre.h"
#include "mipself_test.h"
#include "reloc.h"
enum {CMD_DISP_MEM_PLAGE_OK,  CMD_DISP_MEM_MAP_OK   ,CMD_DISP_REG_OK,CMD_DISP_REG_ALL_OK,ADRS_NON_HEXA,REG_NON_EXISTANT,ERROR,CMD_DISP_REG_PLAGE_OK,PAS_DADRESSE_ENTREE,DEUX_POINT_MANQUANT,NO_VALUE_REG};



int taille(char* chaine);
int cmd_disp(interpreteur inter,mem  memoire,stab  symTAB, map_reg *  mrg);
int test_cmd_dispreg(interpreteur inter,char ** tab_tout_reg,char ** tab_reg_commander,map_reg * mrg);
void erreur_cmd_disp(int verif);
int test_cmd_disp_mem(interpreteur inter,char ** adr1,char ** adr2,mem memoires);
char** init_tab_registre();
void execute_disp_reg(interpreteur inter,char ** tab_reg_demm,int verification,map_reg * mrg);
int reg_exist(char * reg1,char ** tab_tout_reg,int * classement);
void aff(char **m, int b);
int execute_fonction_load(char * file_name,mem * memoire, stab * symtab,stab * symtab_libc) ;
int cmd_load(char * file_name,mem * memoire,stab * symtab,stab * symtab_libc);


#endif





