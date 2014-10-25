#include <stdlib.h>
#include "common/registre.h"
#include "common/notify.h"
#include <string.h>


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
    rm[0]= remplir_registre("$zero", 0, 0);
    //printf ("%s \n",*rm[0]->mnemonique);
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
        if ( (numero <0) || (numero > 32) ) 
        {
            ERROR_MSG("Votre registre n'existe pas.");
        }
        else 
        {
            printf(" %s : %u \n",rm[numero]->mnemonique, (rm[numero]->valeur));
        }
    }

    if (indic==AFFICHE_TOUT) {
        for(i=0; i<31; i++) {
            printf(" %s : %08x \t",rm[i]->mnemonique, (rm[i]->valeur));
            if(i%4==0) {printf("\n");}
        }
    }
    else {
        WARNING_MSG("L'indicateur n'est pas reconnu.");
        return;
    }
printf("\n");}




/* Fonctions associées au numero du registre*/

/* Fonction qui copie la valeur située dans le registre source vers le registre de destination
    > map_reg : pointeur sur l'ensemble 	printf("Première modif via num\n");des registres
    > num_src : numero du registre source
    > num_dest : numero du registre de destination
 */
/*
void copier_reg_reg_via_num (map_reg rm, int num_src, int num_dest) {
    if ( (num_src <0) || (num_src > 31) ) {
        WARNING_MSG("Votre registre source n'existe pas");
    }
    else if( (num_dest <0) || (num_dest > 31) ) {
        WARNING_MSG("Votre registre destination n'existe pas");
    }
    else {
      int valeur=*((rm+num_src)->valeur);
      *((rm+num_dest)->valeur)=valeur;
	printf("Valeur dans registre : %d\n", *((rm+num_dest)->valeur));
      return;
    }
}

// Fonction qui renvoi la valeur stockée dans un registre à partir du numero du registre
uint32_t renvoi_reg_num (map_reg rm, int num) {
    uint32_t valeur;
    if ( (num <0) || (num > 31) ) {
        WARNING_MSG("Votre registre n'existe pas");
        return -1;
    }
    else {
        valeur=*((rm+num)->valeur);
        return valeur;
    }
}

// Fonction qui modifie la valeur stockée dans un registre à partir du numero du registre
void modif_reg_num (int num, map_reg rm, int contenu) {
	int i;
	printf("NUM=%d\n", num);
	if ( (num <0) | (num > 31) ) {
        WARNING_MSG("Votre registre source n'existe pas");
		return;
    }
	if ( (num==0) || (num==26) || (num==27) || (num==28) || (num==30) ) {
    	WARNING_MSG("Vous ne pouvez modifier ce registre");
    	return;
    }
	for(i=0; i<31; i++){
		if (num==( rm + i )->numero) {
			(*(rm+i)->valeur)=contenu;
			return;
		}
	}
    WARNING_MSG("Problème non prévu");
	return;
}



*/
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
/*
int convert_mnemo_num(map_reg rm, char* mnemo) {
	int i;
    int num_cspd;
    for (i=0; i<31; i++) {
        if (strncmp(mnemo,(rm+i)->mnemonique, 3)==0) {
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

char * convert_num_mnemonique(map_reg * rm, int num)  
{
    int i;
    char * mnemo=calloc(64,sizeof(*mnemo));
    for (i=0; i<32; i++)
    {
        if(num==rm[i]->numero) 
        { 
            mnemo=strdup(rm[i]->mnemonique);
            return mnemo;                   
        }
    }
    printf("Votre numero ne correspond pas à un mnemonique connu.");
    mnemo[0]=0;
    return mnemo;
}
*/

// Test reg
int main(){
	//printf("Debut\n");
    map_reg * mrg;
    //int r;
	printf("INITIALISATION DU TABLEAU\n");
    mrg=creer_map_reg();
    printf("INITIALISATION TERMINEE\n");

    affiche_reg(AFFICHE_TOUT,0,mrg);

    // Test via num
//    modif_reg_num(2, mrg, 42);
//    copier_reg_reg_via_num(mrg,2,3);
//    r=renvoi_reg_num (mrg,3);
//	char blabla=r;
	//printf("%c", blabla);

//	affiche_reg(2, 0, 0, mrg);

    // Test via mnemo
    /*
    char*mnemo1;
	mnemo1=calloc(3, sizeof(*mnemo1));
    mnemo1[0]='$';
    mnemo1[1]='v';
    mnemo1[2]='2';
    char*mnemo2;
	mnemo2=calloc(3, sizeof(*mnemo2));
    mnemo2[0]='$';
    mnemo2[1]='v';
    mnemo2[2]='3';
	printf("Debut des soucis\n");
    modif_reg_mnemo(mnemo1, mrg, 49);
    copier_reg_reg_via_mnemo(mrg, mnemo1, mnemo2);
    r=renvoi_reg_mnemo (mrg,mnemo2);
    printf("Valeur dans le registre mnemo 2 : %d \n",'r');
	printf("Jamais deux sans trois \n");

    // Test via dollarnum
    char*dollarnum1;
    dollarnum1[0]='$';
    dollarnum1[1]='6';
    char* dollarnum2;
    dollarnum2[0]='$';
    dollarnum2[1]='7';
    modif_reg_dollarnum(dollarnum1, mrg, 61);
    copier_reg_reg_via_dollarnum(mrg,dollarnum1,dollarnum2);
    r=renvoi_reg_dollarnum (mrg,dollarnum2);
    printf("%d",'r');

	if(*((mrg+2)->pointeur)!=*((mrg+2)->pointeur)) {
		return 1;
	}
	if(*((mrg+4)->pointeur)!=*((mrg+5)->pointeur)) {
		return 1;
	}
	if(*((mrg+6)->pointeur)!=*((mrg+7)->pointeur)) {
		return 1;
	}		
	return 0;
*/
}


