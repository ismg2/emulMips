#include "fonction_token.h"

// fonction qui cherche dans une chaine de caractere ":"
// renvoie 0 si on trouve ":" positif sinon



int cherche_deux_point(char * chaine)
{ int resultat=1; int i=0;
    if(chaine==NULL) resultat=1;

    else 
    {
        while(resultat!=0&&i<strlen(chaine))
        {   
        if(chaine[i]==':') resultat=0;

        else i++;
        }
    }
return resultat;
}




int taille(char* chaine)
{	
int i,compteur=0;
	if(is_hexa_v2(chaine)==0) return CMD_UNKOWN_RETURN_VALUE;
    else for(i=2;i<strlen(chaine);i++) compteur++;
return compteur;
}


// Fonction qui affiche tout les registres demandé , une fois qu'aucune erreur n'a été detecté

void execute_disp_reg(interpreteur inter,char ** tab_reg_demm,int verification,map_reg * mrg)
{int i ;
  switch(verification)
  {
  case CMD_DISP_REG_OK : //DEBUG_MSG("AFFICHAGE d'une liste de registre");
                         //DEBUG_MSG("VOICI LES REGISTRES QUE L'ON VA AFFICHER :");
                         printf("----------------------------------------\n");
                            for (i = 0; i < NBRE_REGISTRE; i++)
                            {
                               if(strcmp(tab_reg_demm[i],"")!=0) 
                                {
                                    int numero;
                                    sscanf(tab_reg_demm[i]+1,"%d",&numero);
                                    //DEBUG_MSG(" %s , ' %d ' ",tab_reg_demm[i],numero);
                                    
                                    affiche_reg (AFFICHE_1,numero,mrg);
                                   
                                }
                            }
                            printf("----------------------------------------\n");
                             break;

  case CMD_DISP_REG_ALL_OK : INFO_MSG("ON AFFICHE TOUT ");
                             affiche_reg (AFFICHE_TOUT,0,mrg); break;

  
    default : WARNING_MSG("POSITION IMPOSSIBLE");
    }

}

// Retourne 0 si les registres existent 1 sinon

int reg_exist(char * reg1,char ** tab_tout_reg,int * classement)
{ int j=0;int erreur=1;
    while(j<70&&erreur!=0)
    {
    if(strcmp(reg1,tab_tout_reg[j])==0)  
    {
        erreur=0;
        *classement=j;
    }
    else j++;   
    }
return erreur;
}

// Initialise une matrice mm taille 70 lignes 64 colonnes

char** init_matrice()
{int i; char ** p;int j;
  p=calloc(70,sizeof(*p));
  if (p==NULL) return NULL;
  else 
  {
     for (i=0 ; i<70 ; i++) 
        {
       p[i]=calloc(64,sizeof (**p));
       if (p[i]== NULL) return NULL;

        }        
    }
    for(j=0;j<70;j++)
    {
        strcpy(p[j],"");
    }
return p;}

//Initiatlisation de tout les registres existant


char ** init_tab_registre()
{ char** tab_compar=init_matrice();
    

    DEBUG_MSG("TABLEAU INITIALISE");


    strcpy(tab_compar[0],"$0");                      strcpy(tab_compar[35],"$zero");                  
    strcpy(tab_compar[1],"$1");                      strcpy(tab_compar[36],"$at");            
    strcpy(tab_compar[2],"$2");                      strcpy(tab_compar[37],"$v0"); 
    strcpy(tab_compar[3],"$3");                      strcpy(tab_compar[38],"$v1");
    strcpy(tab_compar[4],"$4");                      strcpy(tab_compar[39],"$a0");
    strcpy(tab_compar[5],"$5");                      strcpy(tab_compar[40],"$a1");
    strcpy(tab_compar[6],"$6");                      strcpy(tab_compar[41],"$a2");
    strcpy(tab_compar[7],"$7");                      strcpy(tab_compar[42],"$a3");
    strcpy(tab_compar[8],"$8");                      strcpy(tab_compar[43],"$t0");
    strcpy(tab_compar[9],"$9");                      strcpy(tab_compar[44],"$t1");
    strcpy(tab_compar[10],"$10");                    strcpy(tab_compar[45],"$t2");
    strcpy(tab_compar[11],"$11");                    strcpy(tab_compar[46],"$t3");
    strcpy(tab_compar[12],"$12");                    strcpy(tab_compar[47],"$t4");
    strcpy(tab_compar[13],"$13");                    strcpy(tab_compar[48],"$t5");
    strcpy(tab_compar[14],"$14");                    strcpy(tab_compar[49],"$t6");
    strcpy(tab_compar[15],"$15");                    strcpy(tab_compar[50],"$t7");
    strcpy(tab_compar[16],"$16");                    strcpy(tab_compar[51],"$s0");
    strcpy(tab_compar[17],"$17");                    strcpy(tab_compar[52],"$s1");
    strcpy(tab_compar[18],"$18");                    strcpy(tab_compar[53],"$s2");
    strcpy(tab_compar[19],"$19");                    strcpy(tab_compar[54],"$s3");
    strcpy(tab_compar[20],"$20");                    strcpy(tab_compar[55],"$s4");
    strcpy(tab_compar[21],"$21");                    strcpy(tab_compar[56],"$s5");
    strcpy(tab_compar[22],"$22");                    strcpy(tab_compar[57],"$s6");
    strcpy(tab_compar[23],"$23");                    strcpy(tab_compar[58],"$s7");
    strcpy(tab_compar[24],"$24");                    strcpy(tab_compar[59],"$t8");
    strcpy(tab_compar[25],"$25");                    strcpy(tab_compar[60],"$t9");
    strcpy(tab_compar[26],"$26");                    strcpy(tab_compar[61],"$k0");
    strcpy(tab_compar[27],"$27");                    strcpy(tab_compar[62],"$k1");
    strcpy(tab_compar[28],"$28");                    strcpy(tab_compar[63],"$gp");
    strcpy(tab_compar[29],"$29");                    strcpy(tab_compar[64],"$sp");
    strcpy(tab_compar[30],"$30");                    strcpy(tab_compar[65],"$fp");
    strcpy(tab_compar[31],"$31");                    strcpy(tab_compar[66],"$ra");
    strcpy(tab_compar[32],"$32");                    strcpy(tab_compar[67],"$HI");
    strcpy(tab_compar[33],"$33");                    strcpy(tab_compar[68],"$LO");
    strcpy(tab_compar[34],"$33");                    strcpy(tab_compar[69],"$pc");
//aff(tab_compar,70);
return tab_compar;
}


// Verifie si apres disp  et mem les token entrée sont bien une plage avec des adresses hexa
// ou si on demande d'afficher la map


int test_cmd_dispmem(interpreteur inter,char ** tab_mem)
{
    int sortie=0;
    int erreur=0;
    char * adr1=get_next_token(inter);
    char * two_point=get_next_token(inter);
    char * adr2=get_next_token(inter);
    if (strcmp(adr1,"map")==0) {return CMD_DISP_MEM_MAP_OK;} 
    int deux_point=1;
    DEBUG_MSG("adresse analysed test_cmd_dispmem function  '%s' -->  '%s' ",adr1,adr2);
    DEBUG_MSG("LES FAMEUX DEUX POINT '%s' ",two_point);
    int i=0;
    if(two_point!=NULL) 
        {
            deux_point=cherche_deux_point(two_point);
        }
        else deux_point=1;
    while(erreur == 0)
    {
        if(two_point!=NULL) 
        {
            deux_point=cherche_deux_point(two_point);
        }
        else deux_point=1;

        if (adr1==NULL||adr2==NULL) 
        {
            erreur = 1;
            sortie = PAS_DADRESSE_ENTREE;
            
        }
        else if (is_hexa_v2(adr1)==0 || is_hexa_v2(adr2)==0) 
        {
            erreur = 1;
            sortie = ADRS_NON_HEXA;
            
        }
        else if (deux_point==1) 
        {
            erreur = 1;
            sortie = DEUX_POINT_MANQUANT;
            
        }        
        else 
        {
            tab_mem[i] = strdup(adr1);
            i++;
            tab_mem[i] = strdup(adr2);
            i++;
            adr1=get_next_token(inter);
            two_point=get_next_token(inter);
            adr2=get_next_token(inter);
            sortie = CMD_DISP_MEM_PLAGE_OK;
            erreur = 0;
            if (adr1==NULL) {erreur=1;}
        }
    }

   
return sortie;
}

//Execute la commande d'affichage d'une plage d'adresse ou de toute la map
// si map = CMD_DISP_MEM_MAP_OK  on affiche toute la map , sinon juste entre adr1 et adr2 


void execute_disp_mem(char * adr1,char * adr2,int map,mem memoires,stab symtabs)
{ 
    uint32_t pointeur;
    uint32_t adresse1;
    uint32_t adresse2;
	switch(map)
	{
		case CMD_DISP_MEM_PLAGE_OK : 

        sscanf(adr1,"%08x",&adresse1);
        sscanf(adr2,"%08x",&adresse2);
        DEBUG_MSG("DISP %08x -- > %08x",adresse1,adresse2);

            for(pointeur=adresse1;pointeur<adresse2;pointeur++)
            {
                if(pointeur==adresse1) printf("\n 0x%08x : ",pointeur);
                if(pointeur%4==0 && pointeur!=adresse1 ) printf("\n 0x%08x : ",pointeur);
                //DEBUG_MSG("pointeur : 0x%08x",pointeur);
                affiche_byte(memoires,pointeur);
                //printf("\n");
            }
            printf("\n");
        break;
		case CMD_DISP_MEM_MAP_OK : 
        if(memoires==NULL) {WARNING_MSG("ERROR [7] : Aucun programme n'a été chargé en memoire");}
        else
        {   
            print_mem(memoires);
            stab32_print( symtabs);
        }
        break;
		default : WARNING_MSG("POSITION IMPOSSIBLE");
	}
}



// Gere les messages d'erreur ppour la fonction 


void erreur_cmd_disp(verif)
{ switch(verif)
    {
    case ADRS_NON_HEXA : WARNING_MSG(" ERROR [1] : Les adresses entrée ne sont pas hexadecimal ou désignent un emplacement non existant dans la memoire"); break;

    case REG_NON_EXISTANT : WARNING_MSG(" ERROR [2] : Les registres que vous avez indiqué n'existe pas, verifiez que vous avez taper $ avant le nom ou le numero du registre !"); break;

    case ERROR : WARNING_MSG(" ERROR [3] : La fonction disp se trouve dans un emplacement impossible, une erreur a été oublié");break;

    case PAS_DADRESSE_ENTREE : WARNING_MSG("ERROR [4] : Vous n'avez pas entré d'adresse pour afficher la plage de donner que vous voulez !!!!"); break;

    case DEUX_POINT_MANQUANT : WARNING_MSG("ERROR [5] : Verifiez si vous n'avez pas oublier les deux points ou que certaines adresses sont manquantes, ILS SONT ESSENTIEL");break;

    case NO_VALUE_REG : WARNING_MSG("ERROR [6] : PAS DE REGISTRE ENTREE");break;

    default: WARNING_MSG("ERREUR NON REFERENCE");
}

}






//test si la commande d'affichge est correct
//ressort le tableau des registres affichés

//il manque le cas : disp reg $0:$7 ou $at:$pc



int test_cmd_dispreg(interpreteur inter,char ** tab_tout_reg,char ** tab_reg_commander,map_reg * mrg)
{ 
   char * token=get_next_token(inter);
   int indicateur;
   int i=0;
   int numero;
 if(token==NULL) return NO_VALUE_REG;
        
   else if(strcmp(token,"all")==0) return CMD_DISP_REG_ALL_OK;

// Nous avons choisi d'afficher un message d'erreur lorsque un des registres entré n'est pas bon !!!

   else if(reg_exist(token,tab_tout_reg,&indicateur)==0)  
    {   
        while(token != NULL) 
       { 
            if (reg_exist(token, tab_tout_reg,&indicateur)==0)
            {
                if ( indicateur >= 35) 
                {
                    char dollar[32] = "$";
                    numero = convert_mnemo_num(mrg,token);
                    DEBUG_MSG("Le registre %s correspond au numero : %d",token,numero);
                    sprintf(token,"%d",numero);
                    DEBUG_MSG("RETOUR A LA CHAINE DE CARACTERE : %s",token);
                    strcat(dollar,token);
                    strcpy(token,dollar);
                    DEBUG_MSG("RETOUR A LA CHAINE DE CARACTERE AVEC DOLLAR : %s",token);
                }
                tab_reg_commander[i]=strdup(token);
                
            }
            else 
            {
                return REG_NON_EXISTANT;
            }

            token = get_next_token(inter);
            i++;
        }
        
        return CMD_DISP_REG_OK;
    }   
    else    return REG_NON_EXISTANT; 


return ERROR;
}


int cmd_disp(interpreteur inter,mem  memoire,stab  symTAB, map_reg * mrg) 
{
    DEBUG_MSG("Chaine : %s", inter->input);
    int verif;
    char * token=NULL;
    char * adresse1=NULL;
    char * adresse2=NULL;
    char** tab_all_reg=NULL;
    char** tab_reg_dem=NULL;
    char** tab_mem_dem=NULL;
    int i=0;
    tab_mem_dem=init_matrice();
    if((token = get_next_token(inter))!=NULL) 
    {
        if(strcmp(token,"mem")==0)
        {  
            verif = test_cmd_dispmem(inter,tab_mem_dem);
            switch(verif)
            {
                case CMD_DISP_MEM_PLAGE_OK :
                        while(strcmp(tab_mem_dem[i],"")!=0)
                        {
                            adresse1=strdup(tab_mem_dem[i]);
                            i++;
                            adresse2=strdup(tab_mem_dem[i]);
                            i++;
                            execute_disp_mem(adresse1,adresse2,CMD_DISP_MEM_PLAGE_OK,memoire,symTAB);
                            return CMD_OK_RETURN_VALUE;    
                        }
                        
                    break;

                case CMD_DISP_MEM_MAP_OK :
                        execute_disp_mem(adresse1,adresse2,CMD_DISP_MEM_MAP_OK,memoire,symTAB);return CMD_OK_RETURN_VALUE;
                    break;

                default : erreur_cmd_disp(verif); return 1;
                    break;
            }
            
        }    
        else if(strcmp(token,"reg")==0)
        {   DEBUG_MSG("Debut du traitement de la demande d'affichage des registres"); 
            tab_all_reg=init_tab_registre();
            tab_reg_dem=init_matrice();
                verif = test_cmd_dispreg(inter,tab_all_reg,tab_reg_dem,mrg);
                switch(verif)
                {
                case CMD_DISP_REG_OK : execute_disp_reg(inter,tab_reg_dem,CMD_DISP_REG_OK,mrg);return CMD_OK_RETURN_VALUE;break;
                case CMD_DISP_REG_ALL_OK : execute_disp_reg(inter,tab_reg_dem,CMD_DISP_REG_ALL_OK,mrg);return CMD_OK_RETURN_VALUE;break;
                   
                default : erreur_cmd_disp(verif);return 1;break;
                }
        }

        else
        {  
            WARNING_MSG(" Wrong argument given to command %s \n","disp");
            return 1;
        }    
        
    }

    else
    {
            WARNING_MSG("No Argument is given to %s command \n","disp");
            return 1;
    }

return 200;}



void aff(char **m, int b)
{int j;
    for(j=0;j<b;j++)
    {printf(" %s     " ,m[j]);}
}





int cmd_load(char * file_name,mem * memoire,stab * symtab,stab * symtab_libc)
{
    //int verif;
    FILE * pf_elf;

    if ((pf_elf = fopen(file_name,"r")) == NULL) {
        WARNING_MSG("cannot open file %s", file_name);
        return 1;
    }

    else if (!assert_elf_file(pf_elf))
       { DEBUG_MSG("file %s is not an ELF file", file_name);
        return 1;}

    else {
        fclose(pf_elf);return execute_fonction_load(file_name,memoire,symtab,symtab_libc);
            }
}




// le main charge un fichier elf en entrée en utilisant
// les arguments du prototype de la fonction main (cf. fiches infos)
//
int execute_fonction_load(char * file_name,mem * memoire, stab * symtab,stab * symtab_libc) 
{

    char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR};
    unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};
    unsigned int nsegments;
    unsigned int nsegments_;
    int i=0,j=0;
    unsigned int type_machine;
    unsigned int endianness;   //little ou big endian
    unsigned int bus_width;    // 32 bits ou 64bits
    unsigned int next_segment_start = START_MEM; // compteur pour designer le début de la prochaine section


    // on fait le ménage avant de partir
    //del_mem(*memoire);
    //del_stab(*symtab);

    *symtab= new_stab(0); // table des symboles
    *symtab_libc= new_stab(0); // table des symboles de la libc
    FILE * pf_elf, *pf_libc;

    if ((pf_elf = fopen(file_name,"r")) == NULL) {
        DEBUG_MSG("cannot open file %s", file_name);
    }

    if (!assert_elf_file(pf_elf))
        DEBUG_MSG("file %s is not an ELF file", file_name);

    if ((pf_libc = fopen(PATH_TO_LIBC,"r")) == NULL) 
    {
        ERROR_MSG("cannot open file %s", PATH_TO_LIBC);
    }

    if (!assert_elf_file(pf_libc))
        ERROR_MSG("file %s is not an ELF file", PATH_TO_LIBC);



    // recuperation des info de l'architecture
    elf_get_arch_info(pf_elf, &type_machine, &endianness, &bus_width);
    // et des symboles
    elf_load_symtab(pf_elf, bus_width, endianness,symtab);
    elf_load_symtab(pf_libc, bus_width, endianness, symtab_libc);


    nsegments = get_nsegments(*symtab,section_names,NB_SECTIONS);
    nsegments += get_nsegments(*symtab_libc,section_names,NB_SECTIONS);
    nsegments = nsegments + 2 ;
    //DEBUG_MSG("NOMBRE DE SEGMENT : %u",nsegments_);

    // allouer la memoire virtuelle
    *memoire=init_mem(nsegments);

    next_segment_start = LIBC_MEM_START;
    printf("\ndebut : %08x\n",next_segment_start);
    j=0;
//-------------------------------------------------------------------------
        // on alloue libc
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],*symtab_libc)) {
            elf_load_section_in_memory(pf_libc,(*memoire), section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start+= (((*memoire)->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
            (*memoire)->seg[j].start._32 = next_segment_start;
//            print_segment_raw_content(&memoire->seg[j]);
            j++;
        }
    }

    // on reloge libc
    for (i=0; i<j; i++) {
        reloc_segment(pf_libc, (*memoire)->seg[i], *memoire,endianness,symtab_libc,NULL,NULL);
    }

    // on change le nom des differents segments de libc
    for (i=0; i<j; i++) {
        char seg_name [256]= {0};
        strcpy(seg_name,"libc");
        strcat(seg_name,(*memoire)->seg[i].name);
        free((*memoire)->seg[i].name);
        (*memoire)->seg[i].name=strdup(seg_name);
    }
//----------------------------------------------------------------------------
    // On va chercher les sections du fichier
    int k =j;
    next_segment_start = START_MEM;
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],*symtab)) {
            elf_load_section_in_memory(pf_elf,*memoire, section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start+= (((*memoire)->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
            //print_segment_raw_content(&memory->seg[j]);
            j++;
        }
    }

    for (i=k; i<j; i++) {
        reloc_segment(pf_elf, (*memoire)->seg[i], *memoire,endianness,symtab,symtab_libc,pf_libc);

    }
    //print_mem(*memoire);
    //stab32_print(*symtab); 
    // alloue le stack 
    (*memoire)->seg[j].name        = strdup("[stack]");   
    (*memoire)->seg[j].size._32    = 0x800000;    
    (*memoire)->seg[j].start._32   = 0xff7ff000;
    (*memoire)->seg[j].attr        = SCN_ATTR(1, RW_);
    (*memoire)->seg[j].content     = calloc((*memoire)->seg[j].size._32, sizeof(char));
    //print_segment_raw_content(&(*memoire)->seg[k+2]); 
    
    (*memoire)->seg[j+1].name        = strdup("[vsyscall]");
    (*memoire)->seg[j+1].size._32    = 0xfff;  
    (*memoire)->seg[j+1].start._32   = 0xfffff000;  
    (*memoire)->seg[j+1].attr        = SCN_ATTR(1, R_X);
    (*memoire)->seg[j+1].content     = calloc((*memoire)->seg[j+1].size._32, sizeof(char));

    //printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", file_name) ;
       
    INFO_MSG("Programme Charge en memoire");
    printf("-----------------------------------------------------------------------------");


    //stab32_print(*symtab_libc);
    
    fclose(pf_elf);
    fclose(pf_libc);
    puts("");
 return CMD_OK_RETURN_VALUE;}






