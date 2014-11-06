#include "fonction_mem.h"


void affiche_mot (mem virtualm, uint32_t vaddr1) {
    //uint32_t nbre_seg = virtualm->nseg;
    int i, j;
        for(i=0; i < (virtualm->nseg)-1; i++) 
        {
        uint32_t adr_depart_seg1=  (virtualm)->seg[i].start._32;
        uint32_t adr_depart_seg2=  (virtualm)->seg[i+1].start._32;
        if ( vaddr1 >= adr_depart_seg1 &&  vaddr1 < adr_depart_seg2 )
            {
            uint32_t difference = vaddr1 - adr_depart_seg1;
            //DEBUG_MSG("DIFFERENCE : %08x",difference);
            for(j=0; j<4; j++) 
                {
                printf("\n");
                printf("%02x", (virtualm)->seg[i].content[difference+j]);

                }
            printf("\n");
            }
        DEBUG_MSG("Fin de l'adresse");
        }
    //}

    WARNING_MSG("L'adresse demandée n'a pas été retrouvée !");
}


uint32_t renvoi_mot (mem virtualm, uint32_t vaddr1)
{
    //uint32_t nbre_seg = virtualm->nseg;
    uint32_t mot;
    int i, j;
    for(i=0; i < virtualm->nseg; i++) {
        uint32_t adr_depart_seg1=  (virtualm)->seg[i].start._32;
        uint32_t adr_depart_seg2=  (virtualm)->seg[i+1].start._32;
        if ( vaddr1 >= adr_depart_seg1 &&  vaddr1 < adr_depart_seg2 )
        {
            uint32_t difference = vaddr1 - adr_depart_seg1;
            for(j=0; j<4; j++)
            {
                mot = ( mot << 8 ) + (virtualm)->seg[i].content[difference+j]; //On lit un Byte = 8 bits
            }
        return mot;
        }
    }
    WARNING_MSG("L'adresse demandée n'a pas été retrouvée !");
    return 1;
}


