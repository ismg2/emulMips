#include "liste.h"


liste creer_liste(void)
{ return NULL;  } /* la liste vide est representée par NULL */

int est_vide(liste L)
{ return !L; }


void visualiser_liste(liste L) //visualiser_liste

{ printf("\n");
    liste p;
    int i=0;
    if(L==NULL) 
        {
            printf("Il n'y a pas de Break Point !! \n");
        }

    for (p=L;!est_vide(p); p=p->suiv)
    {
        printf("#%d : %04x \n",i,p->val.adresse_BP);
        i++;
    }
 
printf("\n");}


liste ajout_tete(BP C, liste L)
{ liste p=calloc(1,sizeof(*p));
    if (p==NULL) return NULL;
    else {p->val=C;
        p->suiv=L;}
    
    return p;}

liste supprimer_tete(liste L)
{   liste p;
    
    p=L->suiv;
    free(L);
    return p;}

liste ajout_queue(BP C, liste L)
{ liste p; liste k;
    p=calloc(1,sizeof(*p));
    p->val=C;
    if(!est_vide(L))
    {
        for (k=L; !est_vide(k); k=k->suiv);
        L->suiv=p;
        
        return L;
    }
    else p->suiv=NULL;
    
    return p;
}

liste supprimen(int n, liste L)
{ liste p=L;int i=0;liste k;
/**
 * 
 */

    return p;}

liste concat(liste l1, liste l2)
{liste q=NULL;
    
    if(l1==NULL) { return l2; }
    
    for(q=l1;q->suiv!=NULL;q=q->suiv);       //On pintourt tout et on sarrete au bon moment avec q->suiv!=NULL //
    q->suiv=l2;
    
    return l1;
    
}                                         //Il n'arrivent rien a l2 par contre l1 est rallongé //


liste copie(liste l)
{ liste p; liste copie=NULL;
    
    for(p=l;p->suiv!=NULL;p=p->suiv)
    {
        copie->val=p->val;
        copie->suiv=p->suiv; 
    }
    
    return copie;
    
}
