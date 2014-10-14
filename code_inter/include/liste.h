#ifndef _liste_h
#define _liste_h


#include "fonction_base.h"
#include "fonction_token.h"

struct cellule2 {
    int val;
    struct cellule2 * suiv;} ;
typedef struct cellule2* Liste_A;

Liste_A creer_liste(void);
void visualiser_liste(Liste_A L);
Liste_A ajout_tete(int C, Liste_A L);
Liste_A supprimer_tete(Liste_A L);
Liste_A ajout_queue(int C, Liste_A L);
Liste_A supprimen(int n, Liste_A L);
Liste_A concat(Liste_A l1, Liste_A l2);
Liste_A copie(Liste_A l);

#endif