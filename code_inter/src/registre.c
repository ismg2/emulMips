#include "registre.h"


// Fonction : créer ensemble des registres, copier reg dans autre, suppr registre, initialiser registre, transformer mnémonique en numéro

map_reg remplir_registre(char* mnemo, int num, int val)
{
    map_reg  temp = calloc(1, sizeof(*temp));

        temp->numero=num;
        temp->pointeur=&val;
        temp->mnemonique=strdup(mnemo);
    return temp;
}

map_reg * creer_map_reg() 
{
    map_reg *  rm;
    rm=calloc(38,sizeof(*rm));
    rm[0]= remplir_registre("$zero", 0, 0);
        rm[1]= remplir_registre("$at", 1, 0);
    rm[2]= remplir_registre("$v0", 2, 0);
    rm[3]= remplir_registre("$v1", 3, 0);
    rm[4]= remplir_registre("$a0", 4, 0);
    rm[5]= remplir_registre("$a1", 5, 0);
    rm[6]= remplir_registre("$a2", 6, 0);
    rm[7]= remplir_registre("$a3", 7, 0);
    rm[8]= remplir_registre("$t0", 8, 0);
    rm[9]= remplir_registre("$t1", 9, 0);
    rm[10]= remplir_registre("$t2", 10, 0);
    rm[11]= remplir_registre("$t3", 11, 0);
    rm[12]= remplir_registre("$t4", 12, 0);
    rm[13]= remplir_registre("$t5", 13, 0);
    rm[14]= remplir_registre("$t6", 14, 0);
    rm[15]= remplir_registre("$t7", 15, 0);
    rm[16]= remplir_registre("$s0", 16, 0);
    rm[17]= remplir_registre("$s1", 17, 0);
    rm[18]= remplir_registre("$s2", 18, 0);
    rm[19]= remplir_registre("$s3", 19, 0);
    rm[20]= remplir_registre("$s4", 20, 0);
    rm[21]= remplir_registre("$s5", 21, 0);
    rm[22]= remplir_registre("$s6", 22, 0);
    rm[23]= remplir_registre("$s7", 23, 0);
    rm[24]= remplir_registre("$t8", 24, 0);
    rm[25]= remplir_registre("$t9", 25, 0);
    rm[26]= remplir_registre("$k0", 26, 0);
    rm[27]= remplir_registre("$k1", 27, 0);
    rm[28]= remplir_registre("$gp", 28, 0);
    rm[29]= remplir_registre("$sp", 29, 0);
    rm[30]= remplir_registre("$fp", 30, 0);
    rm[31]= remplir_registre("$ra", 31, 0);
return rm;
}


/*
//map_reg creer_map_reg() {
//	char*p;
	





void suppr_reg (map_reg rm, int num) {
    if((rm+num)->mnemonique != NULL) {
        free((rm+num)->mnemonique);
    }
    if((rm+num)->pointeur != NULL) {
        free((rm+num)->pointeur);
    }
    free((rm+num));
}

void suppr_map_reg(map_reg rm) {
	int i;
    if (rm!=NULL){
        for (i=0; i<32; i++){
            suppr_reg(rm,i);
        }
        free(rm);
    }
}
*/
 //Fonction qui renvoie une plage de registre (qui peut se réduire un comme à toute la page)
void affiche_reg (int indic, int origine, int fin, map_reg rm) {
    int i;
    if (indic==1) {
        if ( (origine <0) || (origine > 32) ) {
            ERROR_MSG("Votre registre n'existe pas.");
        }
        else {
            printf("%s : %d",rm[origine].mnemonique, *(rm[origine].pointeur));
            return;
        }
    }
    if (indic==0) {
        if ( (origine <0) || (origine > 32) ) {
            WARNING_MSG("Votre registre d'origine n'existe pas.");
            return;
        }
        else if ( (fin <0) || (fin > 32) ) {
            WARNING_MSG("Votre registre de fin n'existe pas");
            return;
        }
        else {
            for(i=origine; i<fin; i++) {
                printf("%d", *((rm->pointeur)+i));
            }
        }
    }
    if (indic==2) {
        for(i=0; i<32; i++) {
            printf("%d", *((rm->pointeur)+i));
        }
    }
    else {
        WARNING_MSG("L'indicateur n'est pas reconnu.");
        return;
    }
}




/* Fonctions associées au numero du registre*/

/* Fonction qui copie la valeur située dans le registre source vers le registre de destination
    > map_reg : pointeur sur l'ensemble des registres
    > num_src : numero du registre source
    > num_dest : numero du registre de destination
 */
/*
void copier_reg_reg_via_num (map_reg rm, int num_src, int num_dest) {
    if ( (num_src <0) || (num_src > 32) ) {
        WARNING_MSG("Votre registre source n'existe pas");
    }
    else if( (num_dest <0) || (num_dest > 32) ) {
        WARNING_MSG("Votre registre destination n'existe pas");
    }
    else {
      int valeur=*((rm+num_src)->pointeur);
      *((rm+num_dest)->pointeur)=valeur;
      return;
    }
}

int renvoi_reg_num (map_reg rm, int num) {
    int valeur;
    if ( (num <0) || (num > 32) ) {
        WARNING_MSG("Votre registre n'existe pas");
        return -1;
    }
    else {
        valeur=*((rm+num)->pointeur);
        return valeur;
    }
}

void modif_reg_num (int num, map_reg rm, int contenu) {
	int i;
    if ( (num <0) | (num > 32) ) {
        WARNING_MSG("Votre registre source n'existe pas");
    }
    else {
        if (num==( rm + i )->numero) {
            if ( (i=0) || (i=26) || (i=27) || (i=28) || (i=30) ) {
                WARNING_MSG("Vous ne pouvez modifier ce registre");
                return;
            }
            else {
                (*(rm+i)->pointeur)=contenu;
                return;
            }
        }
    }
}



*/
/* Fonction massociée au dollar_numero du registre*/
/*
int convert_dollarnum_num(map_reg rm, char* dollarnum) {
    int result;
    sscanf(dollarnum, "%d", &result);
    return result;
}

void modif_reg_dollarnum (char* dollarnum, map_reg rm, int contenu) {
    int num_assoc=convert_dollarnum_num(rm, dollarnum);
    modif_reg_num(num_assoc, rm, contenu);
    return;
}

int renvoi_reg_dollarnum (map_reg rm, char* dollarnum) {
	int result;
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
/*
int convert_mnemo_num(map_reg rm, char* mnemo) {
	int i;
    int num_cspd;
    for (i=0; i<32; i++) {
        if (mnemo==(rm+i)->mnemonique) {
            num_cspd=(rm+i)->numero;
			return(num_cspd);
        }
    }
    WARNING_MSG("Votre mnemonique ne correspond à aucun registre");
    return 42;
}

void modif_reg_mnemo (char* mnemo, map_reg rm, int contenu) {
    int num_assoc=convert_mnemo_num(rm, mnemo);
    modif_reg_num(num_assoc, rm, contenu);
    return;
}

int renvoi_reg_mnemo (map_reg rm, char* mnemo) {
	int resultat;
    int num_assoc=convert_mnemo_num(rm, mnemo);
    renvoi_reg_num(rm, num_assoc);
    return resultat;
}

void copier_reg_reg_via_mnemo (map_reg rm, char* mnemo_src, char* mnemo_dest) {
    int num_assoc_src=convert_mnemo_num(rm, mnemo_src);
    int num_assoc_dest=convert_mnemo_num(rm, mnemo_dest);
    copier_reg_reg_via_num (rm, num_assoc_src, num_assoc_dest);
    return;
}
*/
char * convert_num_mnemonique(map_reg rm, int num)  
{
	int i;
	char * mnemo=calloc(64,sizeof(*mnemo));
	for (i=0; i<32; i++)
    {
		if(num==rm[i].numero) 
        { 
            mnemo=strdup(rm[i].mnemonique);
			return mnemo;					
		}
	}
	WARNING_MSG("Votre numero ne correspond pas à un mnemonique connu.");
	mnemo[0]=0;
	return mnemo;
}


