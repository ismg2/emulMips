#include "fonction_mem.h"


/**
 * Affichage d'un mot (32 bits)
 * @param virtualm memoire virtuelle
 * @param vaddr1 adresse virtuelle du mot a afficher
 * @return affichage du mot
 */

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

/**
 * renvoie un mot (32 bits)
 * @param virtualm memoire virtuelle
 * @param vaddr1 adresse virtuelle du mot a afficher
 * @param mrg map de tout les registres
 * @return mot de 32 bits du fichier elf ou 1 en cas d'erreur
 */

uint32_t renvoi_mot (mem virtualm, uint32_t vaddr1,map_reg * mrg)
{
    int nbre_seg = (int) virtualm->nseg;
    uint32_t adr_d_stack = 0xff7ff000;
    uint32_t adr_f_stack = 0xfffff000;
    //DEBUG_MSG("NOMBRE DE SEG : %d",nbre_seg);
    uint32_t mot=0;
    int i, j;
    for(i=0; i < nbre_seg; i++) 
    {
        uint32_t adr_depart_seg1=  (virtualm)->seg[i].start._32;
        uint32_t adr_depart_seg2=  (virtualm)->seg[i+1].start._32;
        if ( vaddr1 >= adr_depart_seg1 &&  vaddr1 < adr_depart_seg2 )
        {
            uint32_t difference = vaddr1 - adr_depart_seg1;
            for(j=0; j<4; j++)
            {
            mot = ( mot << 8 ) + (virtualm)->seg[i].content[difference+j];
            }
            return mot;
        }
    }
    WARNING_MSG("L'adresse demandée n'a pas été retrouvée !");
    return 1;
}


/**
 * renvoie un byte (8 bits)
 * @param virtualm memoire virtuelle
 * @param vaddr1 adresse virtuelle du mot a afficher
 * @param mrg map de tout les registres
 * @return byte de 8 bits du fichier elf ou 1 en cas d'erreur
 */

uint8_t renvoi_byte (mem virtualm, uint32_t vaddr1,map_reg * mrg)
{
    int nbre_seg = (int) virtualm->nseg;
    uint32_t adr_d_stack = 0xff7ff000;
    uint32_t adr_f_stack = 0xfffff000;
    //DEBUG_MSG("NOMBRE DE SEG : %d",nbre_seg);
    uint32_t mot=0;
    int i;
    for(i=0; i < nbre_seg; i++) 
    {
        uint32_t adr_depart_seg1=  (virtualm)->seg[i].start._32;
        uint32_t adr_depart_seg2=  (virtualm)->seg[i+1].start._32;
        if ( vaddr1 >= adr_depart_seg1 &&  vaddr1 < adr_depart_seg2 )
        {
            uint32_t difference = vaddr1 - adr_depart_seg1;
            {
                mot = ( mot << 8 ) + (virtualm)->seg[i].content[difference]; //On lit un Byte = 8 bits
            }
        return mot;
        }
    }
    WARNING_MSG("L'adresse demandée n'a pas été retrouvée !");
    return 1;
}

/**
 * On modifie un  byte de la memoire virtuelle
 * Il y a ici un cas a differencier cad cas ou on modifie dans le stack
 * @param virtualm memoire virtuelle
 * @param vaddr1 adresse virtuelle ou il faut modifier un byte
 * @param byte byte a introduire
 * @param mrg map registre
 * @return 1 si succes 0 sinon 
 */

int set_byte (mem virtualm, uint32_t vaddr1,uint8_t byte,map_reg * mrg)
{
    int nbre_seg = (int) virtualm->nseg;
    uint32_t adr_d_stack = 0xff7ff000;
    uint32_t adr_f_stack = 0xfffff000;
    uint32_t size_stack = 0x800000;
    int j;
    //DEBUG_MSG("NOMBRE DE SEG : %d",nbre_seg);
    int i;
    for(i=0; i < nbre_seg; i++) 
    {
        uint32_t adr_depart_seg1=  (virtualm)->seg[i].start._32;
        uint32_t adr_depart_seg2=  (virtualm)->seg[i+1].start._32;
        if ( vaddr1 >= adr_depart_seg1 &&  vaddr1 < adr_depart_seg2 )
        {
            uint32_t difference = vaddr1 - adr_depart_seg1;
            DEBUG_MSG("set_byte à l'adresse %08x : %02x",vaddr1,byte);
            
            if(vaddr1 >= adr_d_stack && vaddr1 < adr_f_stack)
                {
                    //MEGA MOCHE
                    for(j=size_stack-5;j>0;j=j-1)
                    {
                        (virtualm)->seg[i].content[j]=(virtualm)->seg[i].content[j-1];
                       if((virtualm)->seg[i].content[j-1]!=0) DEBUG_MSG("RECOPIE : %02x",(virtualm)->seg[i].content[j-1]);
                    }

                    (virtualm)->seg[i].content[difference] = byte;
                    uint32_t sp = renvoi_reg_num(mrg,29);
                    modif_reg_num(29,mrg,sp+1);

                    

                } 
            else (virtualm)->seg[i].content[difference] = byte;
        return 1;
        }
    }
    WARNING_MSG("L'adresse demandée n'a pas été retrouvée !");
    return 0;
}















