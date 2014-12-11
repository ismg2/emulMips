#include "reloc.h"


/*--------------------------------------------------------------------------  */
/**
 * @param fp le fichier elf original
 * @param seg le segment à reloger
 * @param mem l'ensemble des segments
 * @param endianness le boutisme du programme
 * @param symtab la table des symbole du programme 
 * @param symtab_libc la table des symbole de la libc (NULL si inutile)
 * @param fp_libc le fichier elf de la libc (NULL si inutile)
 *
 * @brief Cette fonction effectue la relocation du segment passé en parametres
 * @brief l'ensemble des segments doit déjà avoir été chargé en memoire.
 *
 * VOUS DEVEZ COMPLETER CETTE FONCTION POUR METTRE EN OEUVRE LA RELOCATION !!
 */
void reloc_segment(FILE* fp, segment seg, mem memory,unsigned int endianness,stab* symtab,stab* symtab_libc,FILE* fp_libc) 
{
    byte *ehdr    = __elf_get_ehdr( fp );
    uint32_t  scnsz  = 0;
    Elf32_Rel *rel = NULL;
    uint32_t V;
    uint32_t AHI;
    uint32_t A;
    uint32_t P;
    uint32_t ALO;
    uint32_t AHL;
    uint32_t S;
    uint32_t word;
    uint32_t word2;
    int i;
    char* reloc_name = malloc(strlen(seg.name)+strlen(RELOC_PREFIX_STR)+1);
    scntab section_tab;
    scntab section_tab_libc;

    // on recompose le nom de la section
    memcpy(reloc_name,RELOC_PREFIX_STR,strlen(RELOC_PREFIX_STR)+1);
    strcat(reloc_name,seg.name);

    // on rÈcupere le tableau de relocation et la table des sections
    rel = (Elf32_Rel *)elf_extract_scn_by_name( ehdr, fp, reloc_name, &scnsz, NULL );
    elf_load_scntab(fp ,32, &section_tab);

    if (symtab_libc!=NULL && fp_libc!=NULL)
        elf_load_scntab(fp_libc ,32, &section_tab_libc);


    if (rel != NULL &&seg.content!=NULL && seg.size._32!=0) 
    {

        INFO_MSG("--------------Relocation de %s-------------------\n",seg.name) ;
        INFO_MSG("Nombre de symboles a reloger: %ld\n",scnsz/sizeof(*rel)) ;
        for(i=0;i<scnsz/sizeof(*rel);i++)
        {
            uint32_t offset = rel[i].r_offset;
            FLIP_ENDIANNESS(offset);
            uint32_t info = rel[i].r_info;
            FLIP_ENDIANNESS(info);
            printf("Elf32_Rel : \n r_offset : %04x \n r_info : %08x \n",offset,info);
            int type_reloc = info & 0xFF;
            int indice_seg = ((info & 0xF00) >>8)+3;
            DEBUG_MSG("On reloc dans le segment numero : %d",indice_seg);
            int res;
            DEBUG_MSG("type de reloc : %08x",type_reloc);
            DEBUG_MSG("ADRESSE DE START : seg.start._32 : %08x",seg.start._32);
            word = renvoi_mot(memory,seg.start._32+offset,NULL);
            //printf(" bip \n");
            word2 = renvoi_mot(memory,seg.start._32+offset+4,NULL);
            DEBUG_MSG(" WORD : %08x",word);

            switch(type_reloc)
            {
                case 2 : 
                DEBUG_MSG("TYPE de RELOC : R_MIPS_32");
                
                DEBUG_MSG("V = S : %08x + A : %08x  ",memory->seg[indice_seg-1].start._32,word);
                V = memory->seg[indice_seg-1].start._32 + word;
                res = set_word(memory,seg.start._32+offset,V,NULL);
                if(res == 0) 
                {
                    WARNING_MSG("Il y a un soucis d'ecriture dans la memoire");
                    
                }
                break;
                case 4 : 
                DEBUG_MSG("TYPE de RELOC : R_MIPS_26");
                A = word & 0x3FFFFFF;
                P = memory->seg[indice_seg-1].start._32+offset;
                S = memory->seg[indice_seg-1].start._32;
                DEBUG_MSG(" S : %08x :: A : %08x :: P : %08x ",S,A,P);
                V = (((A << 2)|(P & 0xF0000000))+S)>>2;
                //DEBUG_MSG("V : %08x",V);
                //DEBUG_MSG("A = %08x",A);
                //DEBUG_MSG("S = %08x",S);
                //DEBUG_MSG("P = %08x",P);
                word = (word & 0xFC000000)|V;
                //DEBUG_MSG(" RECOMPOSITION DE L'INSTRUCTION A construire : %08x",word);
                res = set_word(memory,seg.start._32+offset,word,NULL);
                if(res == 0) 
                {
                    WARNING_MSG("Il y a un soucis d'ecriture dans la memoire");
                    
                }
                break;
                case 5 : 
                DEBUG_MSG("TYPE de RELOC : R_MIPS_HI16");
                AHI = (word & 0xFFFF);
                ALO = (word2 & 0xFFFF);
                AHL = (AHI << 16) + (short)ALO;
                V = ((AHL + S) - (short)(AHL+S))>>16;
                word = ((word & 0xFFFF0000) | (V & 0x0000FFFF));
                res = set_word(memory,seg.start._32+offset,word,NULL);
                if(res == 0) 
                {
                    WARNING_MSG("Il y a un soucis d'ecriture dans la memoire");
                }
                break;
                case 6 : 
                DEBUG_MSG("TYPE de RELOC : R_MIPS_LO16");
                uint32_t S = memory->seg[indice_seg-1].start._32; 
                V = AHL + S;
                word = ((word & 0xFFFF0000) | (V & 0x0000FFFF));
                res = set_word(memory,seg.start._32+offset,word,NULL);
                if(res == 0) 
                {
                    WARNING_MSG("Il y a un soucis d'ecriture dans la memoire");
                }
                break;
                default: WARNING_MSG("Typer de Relocation non reconnu");
            }


        }
    }
}



