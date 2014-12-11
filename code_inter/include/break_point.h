#ifndef _break_point_h
#define _break_point_h

#include "common/notify.h"
#include <string.h>
#include "mem.h"
#include "liste.h"
#include "get_type_token.h"
#include "fonction_base.h"
#include "mipself_test.h"
enum {PAS_ADR,NO_ARGS,PAS_DECALAGE,CARAC_U,DEL_ALL,DEL_1,NON_HEXA,PAS_LOAD,HORS_CODE,POSITION_IMPOS,BP_EXISTANT,BP_EXISTE_PAS,BP_NON_EXIST,PAS_BP,PAS_INST,TROP};



int erreur_fonction_break_point( int verification);
int cmd_break( mem memoire, interpreteur inter, liste * l_breakP);
int execute_add_BP(char * adresse,liste * l_breakP,mem memoire);
int execute_del_BP(char * adresse,liste * l_breakP,int ToR);
int bp_already_here(BP break_p,liste lBP);


#endif
