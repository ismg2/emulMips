#include "common/registre.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Fonction permettant de remplir un registre
    map_reg rm : 
 */
map_reg remplir_registre(char* mnemo, int num, uint32_t val)
{
    map_reg  temp = calloc(1, sizeof(*temp));
        temp->numero=num;
        temp->valeur=val;
        temp->mnemonique=strdup(mnemo);
    return temp;
}

// Fonction qui crée la map_reg en remplissant chaque registre individuellement
map_reg * creer_map_reg() 
{
    map_reg *  rm;
    rm=calloc(38,sizeof(*rm));
    rm[0x00]= remplir_registre("$zero0", 0x0, 0);
    //printf ("%s \n",*rm[0]->mnemonique);
    rm[0x01]= remplir_registre("$at0", 0x1, 0);
    rm[0x02]= remplir_registre("$v00", 0x2, 0);
    rm[0x03]= remplir_registre("$v10", 0x3, 0);
    rm[0x04]= remplir_registre("$a00", 0x4, 0);
    rm[0x05]= remplir_registre("$a10", 0x5, 0);
    rm[0x06]= remplir_registre("$a20", 0x6, 0);
    rm[0x07]= remplir_registre("$a30", 0x7, 0);
    rm[0x08]= remplir_registre("$t00", 0x8, 0);
    rm[0x09]= remplir_registre("$t10", 0x9, 0);
    rm[0xA]= remplir_registre("$t20", 0xA, 0);
    rm[0xB]= remplir_registre("$t30", 0xB, 0);
    rm[0xC]= remplir_registre("$t40", 0xC, 0);
    rm[0xD]= remplir_registre("$t50", 0xD, 0);
    rm[0xE]= remplir_registre("$t60", 0xE, 0);
    rm[0xF]= remplir_registre("$t70", 0xF, 0);
    rm[0x10]= remplir_registre("$s00", 16, 0);
    rm[0x11]= remplir_registre("$s10", 17, 0);
    rm[0x12]= remplir_registre("$s20", 18, 0);
    rm[0x13]= remplir_registre("$s30", 19, 0);
    rm[0x14]= remplir_registre("$s40", 20, 0);
    rm[0x15]= remplir_registre("$s50", 21, 0);
    rm[0x16]= remplir_registre("$s60", 22, 0);
    rm[0x17]= remplir_registre("$s70", 23, 0);
    rm[0x18]= remplir_registre("$t80", 24, 0);
    rm[0x19]= remplir_registre("$t90", 25, 0);
    rm[0x1A]= remplir_registre("$k00", 26, 0);
    rm[0x1B]= remplir_registre("$k10", 27, 0);
    rm[0x1C]= remplir_registre("$gp0", 28, 0);
    rm[0x1D]= remplir_registre("$sp0", 29, 0xff7ff000);
    rm[0x1E]= remplir_registre("$fp0", 30, 0);
    rm[0x1F]= remplir_registre("$ra0", 31, 0);
    rm[0x20]=remplir_registre("$pc0",0x20,0);
    rm[0x21]=remplir_registre("$HI0",33,0);
    rm[0x22]=remplir_registre("$LO0",34,0);
return rm;
}


// Fonction qui permet la supression d'un registre à partir 
/*
void suppr_reg (map_reg * rm, int num) 
{
    if(rm[num]->mnemonique != NULL) 
    {
        free(rm[num]->mnemonique);
    }
    if((rm+num)->pointeur != NULL) 
    {
        free(rm[num]->mnemonique);
    }
    free(rm[num]);
}

void suppr_map_reg(map_reg * rm) 
{
    int i;
    if (rm!=NULL)
    {
        for (i=0; i<31; i++)
        {
            suppr_reg(rm,i);
        }
        free(rm);
    }
}
*/
// Fonction qui renvoie une plage de registre (qui peut se réduire un comme à toute la page)
void affiche_reg (int indic, int numero, map_reg * rm) {
    int i;
    if (indic==AFFICHE_1) 
    {
        if ( (numero <0) || (numero > NBRE_REGISTRE) ) 
        {
            WARNING_MSG("Votre registre n'existe pas.");
        }
        else 
        {
            printf(" %s : %04x \t",rm[numero]->mnemonique, (rm[numero]->valeur));
        }
    }

    else if (indic==AFFICHE_TOUT) {
        printf("\n-------------------------------------------------------------------------------\n");
        for(i=0; i<NBRE_REGISTRE; i++) {
            printf(" %s : 0x%08x \t",rm[i]->mnemonique, (rm[i]->valeur));
            if(i%4==0) {printf("\n");}
        }
        printf("\n-------------------------------------------------------------------------------\n");
    }
    else {
        WARNING_MSG("L'indicateur n'est pas reconnu.");
        return;
    }
printf("\n");}




/* Fonctions associées au numero du registre*/

/* Fonction qui copie la valeur située dans le registre source vers le registre de destination
    > map_reg : pointeur sur l'ensemble     printf("Première modif via num\n");des registres
    > num_src : numero du registre source
    > num_dest : numero du registre de destination
 */
void copier_reg_reg_via_num (map_reg * rm, int num_src, int num_dest) {
    if ( (num_src <0) || (num_src > NBRE_REGISTRE) ) {
        WARNING_MSG("Votre registre source n'existe pas");
    }
    else if( (num_dest <0) || (num_dest > NBRE_REGISTRE) ) {
        WARNING_MSG("Votre registre destination n'existe pas");
    }
    else {
      int valeur=rm[num_src]->valeur;
      rm[num_dest]->valeur=valeur;
    printf("Valeur dans registre %s : %d\n",rm[num_dest]->mnemonique,rm[num_dest]->valeur);
      return;
    }
}


// Fonction qui renvoi la valeur stockée dans un registre à partir du numero du registre
uint32_t renvoi_reg_num (map_reg * rm, int num) {
    uint32_t valeur;
    if ( (num <0) || (num > NBRE_REGISTRE) ) 
    {
        WARNING_MSG("Votre registre n'existe pas");
        return -1;
    }
    else 
    {
        valeur=rm[num]->valeur;
        return valeur;
    }
}


// Fonction qui modifie la valeur stockée dans un registre à partir du numero du registre
void modif_reg_num (int num, map_reg * rm, int contenu) {
    int i;
    if ( (num <0) | (num > NBRE_REGISTRE) ) {
        WARNING_MSG("Votre registre source n'existe pas");
        return;
    }
    for(i=0; i<NBRE_REGISTRE; i++)
    {
        if (num==rm[i]->numero) 
        {
            rm[i]->valeur=contenu;
            return;
        }
    }
    WARNING_MSG("Problème non prévu");
}




/* Fonction massociée au dollar_numero du registre*/

/*
int convert_dollarnum_num(map_reg rm, char* dollarnum) {
    int result;
    sscanf(dollarnum, "%d", result);
    return result;
}

void modif_reg_dollarnum (char* dollarnum, map_reg rm, int contenu) {
    int num_assoc=convert_dollarnum_num(rm, dollarnum);
    modif_reg_num(num_assoc, rm, contenu);
    return;
}

uint32_t renvoi_reg_dollarnum (map_reg rm, char* dollarnum) {
    uint32_t result;
    int num_assoc=convert_dollarnum_num(rm, dollarnum);
    result=renvoi_reg_num(rm, num_assoc);
    return result;
}

void copier_reg_reg_via_dollarnum (map_reg rm, char* dollarnum_src, char* dollarnum_dest) {
    int num_assoc_src=convert_dollarnum_num(rm, dollarnum_src);
    int num_assoc_dest=convert_dollarnum_num(rm, dollarnum_dest);
    copier_reg_reg_via_num (rm, num_assoc_src, num_assoc_dest);
    return ;
}


*/
/* Fonctions associées au mnemonique*/

int convert_mnemo_num(map_reg * rm, char * mnemo){
	int num_cspd;
	int i;
	for(i=0; i<35; i++){
		if(strcmp(mnemo, rm[i]->mnemonique)==0){
			num_cspd=rm[i]->numero;
			return num_cspd;
		}
	}
	WARNING_MSG("Le mnemonique ne correspond à aucun registre.");
	return 42;
}	

/*
void modif_reg_mnemo (char* mnemo, map_reg rm, int contenu) {
    int num_assoc=convert_mnemo_num(rm, mnemo);
    modif_reg_num(num_assoc, rm, contenu);
    printf("Contenu théorique : %d \n", contenu);
    printf("Contenu du pointeur : %d \n", *((rm+num_assoc)->pointeur));
    return;
}

uint32_t renvoi_reg_mnemo (map_reg rm, char* mnemo) {
    uint32_t resultat;
    int num_assoc=convert_mnemo_num(rm, mnemo);
    renvoi_reg_num(rm, num_assoc);
    return resultat;
}

void copier_reg_reg_via_mnemo (map_reg rm, char* mnemo_src, char* mnemo_dest) {
    int num_assoc_src=convert_mnemo_num(rm, mnemo_src);
    int num_assoc_dest=convert_mnemo_num(rm, mnemo_dest);
    printf("num_assoc_src : %d \n", num_assoc_src);
    printf("num_assoc_dest : %d \n", num_assoc_dest);
    copier_reg_reg_via_num (rm, num_assoc_src, num_assoc_dest);
    return;
}
*/
char * convert_num_mnemonique(map_reg * rm, int num)  
{
    int i;
    char * mnemo=calloc(64,sizeof(*mnemo));
    for (i=0; i<NBRE_REGISTRE; i++)
    {
        if(num==rm[i]->numero) 
        { 
            mnemo=strdup(rm[i]->mnemonique);
            return mnemo;                   
        }
    }
    WARNING_MSG("Votre numero ne correspond pas à un mnemonique connu.");
    mnemo[0]=0;
    return mnemo;
}

