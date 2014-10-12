#include "liste.h"


Liste_A creer_liste(void)
{ return NULL;  } /* la liste vide est representée par NULL */

int est_vide(Liste_A L)
{ return !L; }


void visualiser_liste(Liste_A L) //visualiser_liste

{ Liste_A p;
    for (p=L;!est_vide(p); p=p->suiv)
 {puts("");
 printf("Arc de %d à %d et une distance %lf et pheromones = %lf",(p->val).debut,(p->val).fin,(p->val).dist,(p->val).quantite_pheromone);
 puts("");
}
 
}


Liste_A ajout_tete(Arc C, Liste_A L)
{ Liste_A p=calloc(1,sizeof(*p));
    if (p==NULL) return NULL;
    else {p->val=C;
        p->suiv=L;}
    
    return p;}

Liste_A supprimer_tete(Liste_A L)
{   Liste_A p;
    
    p=L->suiv;
    free(L);
    return p;}

Liste_A ajout_queue(Arc C, Liste_A L)
{ Liste_A p; Liste_A k;
    p=calloc(1,sizeof(*p));
    p->val=C;
    if(!est_vide(L))
    {
        for (k=L; !est_vide(k); k=k->suiv);
        L->suiv=p;
        
        return L;
    }
    else p->suiv=NULL;
    
    return p;}

Liste_A supprimen(int n, Liste_A L)
{ Liste_A p; Liste_A k;int i=1;
    
    puts("je sais pas comment faire essaye le reste !!!");
    return 0;}

Liste_A concat(Liste_A l1, Liste_A l2)
{Liste_A q=NULL;
    
    if(l1==NULL) { return l2; }
    
    for(q=l1;q->suiv!=NULL;q=q->suiv);       //On parcourt tout et on sarrete au bon moment avec q->suiv!=NULL //
    q->suiv=l2;
    
    return l1;
    
}                                         //Il n'arrivent rien a l2 par contre l1 est rallongé //


Liste_A copie(Liste_A l)
{ Liste_A p; Liste_A copie;
    
    for(p=l;p->suiv!=NULL;p=p->suiv)
    {
        copie->val=p->val;
        copie->suiv=p->suiv; 
    }
    
    return copie;
    
}
