#include "fonction_mem.h"


void affiche_mot (mem virtualm, uint32_t vaddr1) {
    uint32_t nbre_seg = virtualm->nseg;
    DEBUG_MSG("NOMBRE DE SEGMENT : %u",nbre_seg);
    uint32_t ext=(virtualm)->extent._32;
    //DEBUG_MSG("EXTENT MEMOIRE : %08x ------ %u",ext,ext);

    int i, j;

    uint32_t size_seg=(virtualm)->seg[nbre_seg-1].size._32;
    //DEBUG_MSG("SIZE_SEG : %08x",size_seg);


    uint32_t adr_deb_dernier_seg = (virtualm)->seg[nbre_seg-1].start._32;
    //DEBUG_MSG("adr_deb_dernier_seg : %08x",adr_deb_dernier_seg);

    uint32_t adresse_fin =  adr_deb_dernier_seg + size_seg;
    //DEBUG_MSG("adresse_fin : %08x",adresse_fin);


    // Test d'appartenance à la mémoire
    /*
    if(vaddr1 < 0 || vaddr1 > adresse_fin) 
    {
        WARNING_MSG("L'adresse demandée n'appartient pas à la mémoire");
    }
    */
    //else 
    //{
        //Parcours des différents segments
        for(i=0; i < (virtualm->nseg)-1; i++) 
        {
        uint32_t adr_depart_seg1=  (virtualm)->seg[i].start._32;
        uint32_t adr_depart_seg2=  (virtualm)->seg[i+1].start._32;
        DEBUG_MSG("adr_depart_seg %d : %08x",i,adr_depart_seg1);
        DEBUG_MSG("adr DEMANDE : %08x",vaddr1);
        DEBUG_MSG("adr_depart_seg %d : %08x",i+1,adr_depart_seg2);

        if (adr_depart_seg1 >= vaddr1 && adr_depart_seg2 < vaddr1 )
            {
            uint32_t difference = vaddr1 - adr_depart_seg1;
            DEBUG_MSG("DIFFERENCE : %08x",difference);
            for(j=0; j<4; j++) 
                {
                DEBUG_MSG("ON RENTRE");
                printf("%02x", (virtualm)->seg[i].content[difference+j]);
                }
            }
        }
    //}

    WARNING_MSG("L'adresse demandée n'a pas été retrouvée !");
}
/*

byte* renvoi_mot (mem virtualm, int vaddr1) {
    int nbre_seg = virtualm->nseg;
    int difference, i, j;
    byte* mot;
    vsize size_seg=((virtualm->seg)+nbre_seg)->size;
    int adresse_fin = (int) & (((virtualm->seg)+nbre_seg)->start + size_seg);

    // Test d'appartenance à la mémoire
    if(vaddr1 < 0 | vaddr1 > adresse_fin) {
        WARNING_MSG("L'adresse demandée n'appartient pas à la mémoire.");
        return NULL;
    }

    //Parcours des différents segments
    for(i=0; i < virtualm->nseg; i++) {
        int adr_depart_seg1= (int) & ((virtualm->seg)+i)->start;
        int adr_depart_seg2= (int) & ((virtualm->seg)+i+1)->start;
        if (adr_depart_seg1 > vaddr1 | adr_depart_seg2 < vaddr1 ){
            difference = vaddr1 - adr_depart_seg1;
            for(j=0; j<4; j++) {
                mot[i]=*((((virtualm->seg)+i)->content)+difference+j);
            }
            return NULL;
        }
    }
    WARNING_MSG("L'adresse demandée n'a pas été retrouvée !");
    return NULL;
}

*/

