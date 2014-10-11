#ifndef _fonction_token_h
#define _fonction_token_h

#include "fonction_base.h"
#include <ctype.h>
enum {CMD_DISP_MEM_PLAGE_OK,  CMD_DISP_MEM_MAP_OK   ,CMD_DISP_REG_OK,CMD_DISP_REG_ALL_OK,ADRS_NON_HEXA,REG_NON_EXISTANT,ERROR,CMD_DISP_REG_PLAGE_OK,PAS_DADRESSE_ENTREE,DEUX_POINT_MANQUANT,NO_VALUE_REG};

int lettre_hexa(char * chaine);
int is_hexa_v2(char* chaine);
int inf_8(char* chaine);
int is_octal(char * chaine);
int taille(char* chaine);
int is_decimal(char* chaine);
int cmd_disp(interpreteur inter);
void cmd_load(interpreteur inter);
int test_cmd_dispreg(interpreteur inter,char ** tab_tout_reg,char ** tab_reg_commander);
void erreur_cmd_disp(int verif);
int test_cmd_dispmem(interpreteur inter,char * adr1,char * adr2);
char** init_tab_registre();
void execute_disp_reg(interpreteur inter,char ** tab_reg_demm,int verification);
int reg_exist(char * reg1,char ** tab_tout_reg);
void aff(char **m, int b);
int is_byte(char* chaine);
int is_word(char* chaine);
int is_bit(char * chaine);



#endif





