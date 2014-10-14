#ifndef _fonction_base_h
#define _fonction_base_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_type_token.h"
#include "mem.h"
#include "mipself_test.h"

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* macros de DEBUG_MSG fournies , etc */
#include "common/notify.h"


/* prompt du mode shell interactif */
#define PROMPT_STRING "MipsShell : > "

/* taille max pour nos chaines de char */
#define MAX_STR 1024



/*************************************************************\
Valeur de retour speciales lorsqu'on pour la fonction
	int parse_and_execute_cmd_string(char *input) ;
Toute autre valeur signifie qu'une erreur est survenue
 \*************************************************************/
#define CMD_OK_RETURN_VALUE 0
#define CMD_EXIT_RETURN_VALUE -1
#define CMD_UNKOWN_RETURN_VALUE -2




/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT,DEBUG_MODE} inter_mode;

/* structure passée en parametre qui contient la connaissance de l'état de
 * l'interpréteur 
 */
typedef struct {
    inter_mode mode;
    char input[MAX_STR];
    char * from;
    char first_token;
} *interpreteur;

interpreteur init_inter(void);
void del_inter(interpreteur inter);
char* get_next_token(interpreteur inter);
int _testcmd(int hexValue);
int testcmd(interpreteur inter);
int exitcmd(interpreteur inter);
int execute_cmd(interpreteur inter);
void string_standardise( char* in, char* out );
int  acquire_line(FILE *fp, interpreteur inter);
void usage_ERROR_MSG( char *command );




#endif




