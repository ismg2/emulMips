#ifndef _liste_h
#define _liste_h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/notify.h"




typedef struct { uint32_t adresse_BP; } BP;

struct cellule2 {
    BP val;
    struct cellule2 * suiv;} ;
typedef struct cellule2* liste;

liste creer_liste(void);
void visualiser_liste(liste L);
liste ajout_tete(BP C, liste L);
liste supprimer_tete(liste L);
liste ajout_queue(BP C, liste L);
liste supprimen(uint32_t adr, liste L);
liste concat(liste l1, liste l2);
liste copie(liste l);
liste ranger_ordre_croissant(liste l);

#endif