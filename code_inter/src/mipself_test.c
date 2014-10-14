#include "mipself_test.h"




// Fonction permettant de verifier si une chaine de caracteres
// est bien dans la liste des symboles du fichier ELF
// parametres :
// 		name : le nom de la chaine recherch�e
//  symtab : la table des symboles
//
// retourne 1 si present, 0 sinon
int is_in_symbols(char* name, stab symtab) {
    int i;
    for (i=0; i<symtab.size; i++) {
        if (!strcmp(symtab.sym[i].name,name)) return 1;
    }
    return 0;
}

// Cette fonction calcule le nombre de segments � prevoir
// Elle cherche dans les symboles si les sections predefinies
// s'y trouve
// parametres :
//  symtab : la table des symboles
//
// retourne le nombre de sections trouv�es

unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections) {
    unsigned int n=0;
    int i;
    for (i=0; i<nb_sections; i++) {
        if (is_in_symbols(section_names[i],symtab)) n++;
    }
    return n;
}


// fonction permettant d'extraire une section du fichier ELF et de la charg�e dans le segment du m�me nom
// parametres :
//   fp         : le pointeur du fichier ELF
//   memory     : la structure de m�moire virtuelle
//   scn        : le nom de la section � charger
//   permission : l'entier repr�sentant les droits de lecture/ecriture/execution
//   add_start  : l'addresse virtuelle � laquelle la section doit �tre charg�e
//
// retourne 0 en cas de succes, une valeur non nulle sinon
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start) {
    byte *ehdr    = __elf_get_ehdr( fp );
    byte *content = NULL;
    uint  textsz  = 0;
    vsize sz;
    vaddr addr;

    byte *useless = elf_extract_section_header_table( ehdr, fp );
    free( useless );

    if ( NULL == ehdr ) {
        WARNING_MSG( "Can't read ELF file" );
        return 1;
    }

    if ( 1 == attach_scn_to_mem(memory, scn, SCN_ATTR( WIDTH_FROM_EHDR( ehdr ), permissions ) ) ) {
        WARNING_MSG( "Unable to create %s section", scn );
        free( ehdr );
        return 1;
    }

    content = elf_extract_scn_by_name( ehdr, fp, scn, &textsz, NULL );
    if ( NULL == content ) {
        WARNING_MSG( "Corrupted ELF file" );
        free( ehdr );
        return 1;
    }

    switch( WIDTH_FROM_EHDR(ehdr) ) {
    case 32 :
        sz._32   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._32 = add_start;
        break;
    case 64 :
        sz._64   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._64 = add_start;
        break;
    default :
        WARNING_MSG( "Wrong machine width" );
        return 1;
    }

    if ( 1 == fill_mem_scn(memory, scn, sz, addr, content ) ) {
        free( ehdr );
        free( content );
        WARNING_MSG( "Unable to fill in %s segment", scn );
        return 1;
    }

    free( content );
    free( ehdr );

    return 0;
}

// fonction affichant les octets d'un segment sur la sortie standard
// parametres :
//   seg        : le segment de la m�moire virtuelle � afficher

void print_segment_raw_content(segment* seg) {
    int k;
    int word =0;
    if (seg!=NULL && seg->size._32>0) {
        for(k=0; k<seg->size._32; k+=4) {
            if(k%16==0) printf("\n  0x%08x ",k);
            word = *((unsigned int *) (seg->content+k));
            FLIP_ENDIANNESS(word);
            printf("%08x ",	word);
        }
    }
}


int cmd_load(char * file_name,mem * memoire,stab * symtab)
{
    //int verif;
    FILE * pf_elf;

    if ((pf_elf = fopen(file_name,"r")) == NULL) {
        DEBUG_MSG("cannot open file %s", file_name);
        return 1;
    }

    else if (!assert_elf_file(pf_elf))
       { DEBUG_MSG("file %s is not an ELF file", file_name);
        return 1;}

    else {
        fclose(pf_elf);return execute_fonction_load(file_name,memoire,symtab);
            }
}






// le main charge un fichier elf en entr�e en utilisant
// les arguments du prototype de la fonction main (cf. fiches infos)
//
int execute_fonction_load(char * file_name,mem * memoire, stab * symtab) 
{

    char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR};
    unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};
    unsigned int nsegments;
    int i=0,j=0;
    unsigned int type_machine;
    unsigned int endianness;   //little ou big endian
    unsigned int bus_width;    // 32 bits ou 64bits
    unsigned int next_segment_start = START_MEM; // compteur pour designer le d�but de la prochaine section

    *symtab= new_stab(0); // table des symboles
    FILE * pf_elf;

    if ((pf_elf = fopen(file_name,"r")) == NULL) {
        DEBUG_MSG("cannot open file %s", file_name);
    }

    if (!assert_elf_file(pf_elf))
        DEBUG_MSG("file %s is not an ELF file", file_name);


    // recuperation des info de l'architecture
    elf_get_arch_info(pf_elf, &type_machine, &endianness, &bus_width);
    // et des symboles
    elf_load_symtab(pf_elf, bus_width, endianness,symtab);//


    nsegments = get_nsegments(*symtab,section_names,NB_SECTIONS);

    // allouer la memoire virtuelle
    *memoire=init_mem(nsegments);

    // Ne pas oublier d'allouer les differentes sections
    j=0;
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],*symtab)) {
            elf_load_section_in_memory(pf_elf,*memoire, section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start+= (((*memoire)->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k supp�rieur
//            print_segment_raw_content(&memory->seg[j]);
            j++;
        }
    }

    //TO DO allouer la pile (et donc modifier le nb de segments)

    //printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", file_name) ;
    //print_mem(memoire);
    DEBUG_MSG("Programme Charge en memoire");
    printf("-----------------------------------------------------------------------------");
    //stab32_print( symtab);

    // on fait le m�nage avant de partir
    //del_mem(memory);
    //del_stab(symtab);
    fclose(pf_elf);
    puts("");
return 1;}
