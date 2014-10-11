#include<stlib.h>
#include<fonctions.h>
#include"registre.h"


/* Registres */

// Fonction : créer ensemble des registres, copier reg dans autre, suppr registre, initialiser registre, 

map_reg remplir_registre(char* mnemo, int num, int val){
    map_registre registre = calloc(1, sizeof(*registre));
    if ( NULL == registre ) {
        WARNING_MSG( "Impossible d'allouer de la mémoire pour le registre" );
        return NULL;
    }
    else {
        registre->numero=num;
        registre->(*pointeur)=val;
        registre->mnemonique=strdup(mnemo);
    return registre;
}

map_reg creer_map_registre() {
    map_reg rm;
    rm.registre[0]= remplir_registre($zero, 0, 0);
    rm.registre[1]= remplir_registre($at, 1, 0);
    rm.registre[2]= remplir_registre($v0, 2, 0);
    rm.registre[3]= remplir_registre($v1, 3, 0);
    rm.registre[4]= remplir_registre($v2, 4, 0);
    rm.registre[5]= remplir_registre($v3, 5, 0);
    rm.registre[6]= remplir_registre($v4, 6, 0);
    rm.registre[7]= remplir_registre($v5, 7, 0);
    rm.registre[8]= remplir_registre($t1, 8, 0);
    rm.registre[9]= remplir_registre($t2, 9, 0);
    rm.registre[10]= remplir_registre($t3, 10, 0);
    rm.registre[11]= remplir_registre($t4, 11, 0);
    rm.registre[12]= remplir_registre($t5, 12, 0);
    rm.registre[13]= remplir_registre($t6, 13, 0);
    rm.registre[14]= remplir_registre($t7, 14, 0);
    rm.registre[15]= remplir_registre($t8, 15, 0);    
    rm.registre[16]= remplir_registre($s1, 16, 0);
    rm.registre[17]= remplir_registre($s2, 17, 0);
    rm.registre[18]= remplir_registre($s3, 18, 0);
    rm.registre[19]= remplir_registre($s4, 19, 0);
    rm.registre[20]= remplir_registre($s5, 20, 0);    
    rm.registre[21]= remplir_registre($s6, 21, 0);
    rm.registre[22]= remplir_registre($s7, 22, 0);
    rm.registre[23]= remplir_registre($s8, 23, 0);
    rm.registre[24]= remplir_registre($t8, 24, 0);
    rm.registre[25]= remplir_registre($t9, 25, 0);
    rm.registre[26]= remplir_registre($k0, 26, 0);
    rm.registre[27]= remplir_registre($k1, 27, 0);
    rm.registre[28]= remplir_registre($gp, 28, 0);
    rm.registre[29]= remplir_registre($sp, 29, 0);
    rm.registre[30]= remplir_registre($fp, 30, 0);
    rm.registre[31]= remplir_registre($ra, 31, 0);
}

void modifier_registre_mnemonique (char* mnemo, map_reg rm, int contenu) {
    for (i=0; i<31, i++) {
        if (mnemo==(rm+i)->mnemonique) {
            if (i=0 || i=26 || i=27 || i=28 || i=30) {
                WARNING_MSG("Vous ne pouvez modifier ce registre");
                return NULL;
            }
            else {
            (rm+i)->(*pointeur)=contenu;
                return NULL;
            }
        }
    }
}

void modifier_registre_numero (int num, map_registre rm, int contenu) {
    if (num==(rm+i)->numero) {
        if (i=0 || i=26 || i=27 || i=28 || i=30) {
            WARNING_MSG("Vous ne pouvez modifier ce registre");
            return NULL;
        }
        else {
            (rm+i)->(*pointeur)=contenu;
            return NULL;
        }
    }
}

void copier_reg_reg (map_reg rm, int num_src, int num_obj) {

}


