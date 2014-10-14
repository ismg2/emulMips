#ifndef _get_type_token_h
#define _get_type_token_h

#include "fonction_base.h"

// type de token  
enum {UNKNOWN,HEXA,DECIMAL,BINAIRE,BYTE,WORD};
int get_type(char* chaine);
int is_word_byte(char* chaine);
int lettre_hexa(char * chaine);
int is_hexa_v2(char* chaine);
int is_binary(char * chaine);
int inf_8(char* chaine);
int is_decimal(char* chaine);

#endif