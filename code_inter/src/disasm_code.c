#include "disasm_code.h"

/**
 * Lecture du fichier texte regroupant toutes les commandes et affiche le tableau memmoire allooué pour
 * @param file_name : nom du dictionnaire de toutes les commandes
 */
definition lecture_dictionnaire(char * file_name)
{
    
FILE * fp;
fp=fopen(file_name,"r");
char * ligne = NULL;
definition def = NULL;
definition temp = NULL;
def = calloc(1028,sizeof(*def));
temp = calloc(2,sizeof(*def));
ligne = calloc (2054,sizeof(*ligne));
int i;
 
if(fp==NULL)  
  {
    WARNING_MSG("Impoosible d'ouvrir le fichier de Dictionnaire ");
  }
else 
{
  int j=0;

  while(fgets(ligne,2054,fp)!=NULL)
  { 
    //printf("---------------------------------------------------\n");
    //printf("---------------------------------------------------\n");
    //printf("\n LIGNE : %s \n",ligne);
      char * token=strtok(ligne,"   ");
      sscanf(token,"%s",(def[j].nom));
      //printf("\n NOM : %s",(def[j].nom));

      token=strtok(NULL,"   ");
      sscanf(token,"%s",&(def[j].type));
      //printf("\n TYPE : %c ",def[j].type);

      token=strtok(NULL,"   ");
      sscanf(token,"%x",&(temp->signature));
      def[j].signature = (temp->signature);
      //printf("\n SIGNATURE : %08x ",def[j].signature);


      token=strtok(NULL,"   ");
      sscanf(token,"%x",&(temp->masque));
      def[j].masque = temp->masque;
      //printf("\n MASQUE: %08x",def[j].masque);


      token=strtok(NULL,"   ");
      sscanf(token,"%d",&(def[j].nmbr_oper));
      //printf("\n NBR OPERANDE : %d\n",def[j].nmbr_oper);
      if(def[j].nmbr_oper!=0)
      {
        for (i = 0; i < def[j].nmbr_oper ; i++)
          { token=strtok(NULL,"   ");
            char * tempo = calloc(2,sizeof(*tempo));
            sscanf(token,"%s",tempo);
            def[j].op_mapping[i]=strdup(tempo);
           // printf("\t OPERANDE numero %d : %s\n",i+1,def[j].op_mapping[i]);
          }
      }

      token=strtok(NULL,"   ");
      sscanf(token,"%d",&(temp->num_function));
      def[j].num_function = temp->num_function;
      //printf("Numero de la fonction : %d \n",def[j].num_function);
      //printf("\n\n\n");
      j++;
    }
}
fclose(fp);
return def;
}

/**
 * Lance l'execution des programmes de desassamblage selon la commande faites par l'utilisateur
 * @param  inter Commande entrée par l'utilisateur
 * @return       vers les differentes fonction utile
 */

int cmd_disasm(interpreteur inter,mem  memoire,map_reg * mrg)
{
  int verif;
  uint32_t adresse1;
  uint32_t adresse2;
  int deca;
  verif = test_cmd_disasm(inter,&adresse1,&adresse2,&deca);
  switch(verif)
  {
    case CMD_DISASM_OK_PLAGE : 
        DEBUG_MSG("CMD_DISASM_OK_PLAGE");
        DEBUG_MSG(" LA PLAGE A AFFICHER %08x --> %08x ",adresse1,adresse2);  
        return execute_cmd_disasm(adresse1,adresse2,deca,CMD_DISASM_OK_PLAGE,memoire,mrg);
        //return 0;
    break;

    case CMD_DISASM_OK_DECALAGE : 
        DEBUG_MSG("CMD_DISASM_OK_DECALAGE");
        DEBUG_MSG(" LA PLAGE A AFFICHER %08x + %d ",adresse1,deca);
        return execute_cmd_disasm(adresse1,adresse2,deca,CMD_DISASM_OK_DECALAGE,memoire,mrg);
        break;
    
    default : erreur_fonction_disasm(verif);
  }

//return 1;
return CMD_OK_RETURN_VALUE;}



/**
 * Test si les commandes entré par l'utilisateur sont corrects
 * @param  inter Commande entrée par l'utilisateur
 * @param  adr1,adr2 Adresse demandé pour l'affichage du code à dessasembler
 * @param  decalage Decalage donnant le nombre de ligne de code a afficher
 * @return  variable d'erreur ou cmd d'execution des fonctions
 */


int test_cmd_disasm(interpreteur inter, uint32_t * adr1, uint32_t * adr2,int * decalage)
{
  uint32_t temp_adr1;

  char * token=get_next_token(inter);
  if(token==NULL) return PAS_ADRESSE;
  else if(is_hexa_v2(token)==0) return ADRS_NON_HEXA3;
  else {
    sscanf(token,"%x",&temp_adr1);
    *adr1 = temp_adr1;
    if (*adr1<0x3000) return HORS_ZONE_TEXTE;
    token=get_next_token(inter);
    if (token == NULL) return ERREUR_SYNTAXE;
    else if(strcmp(token,"+")==0)
            {   
                token=get_next_token(inter);
                if (token == NULL) return PAS_ADRESSE;
                int temp_decalage;
                sscanf(token,"%d",&temp_decalage);
                if(temp_decalage % 4 != 0) return MAUVAIS_DECALAGE;
                else {
                          *decalage = temp_decalage;
                          return CMD_DISASM_OK_DECALAGE;
                     }
            }
    else if(strcmp(token,":")==0)
            {   token=get_next_token(inter);
                if ( token == NULL) return PAS_ADRESSE;
                else if(is_hexa_v2(token)==0) return ADRS_NON_HEXA3;
                else
                { 
                  uint32_t temp_adr2;
                  sscanf(token,"%x",&temp_adr2);
                  int dif = ((int)temp_adr2 - (int)*adr1)%4;
                  DEBUG_MSG(" ADR2 %d :: ADR1 %d",temp_adr2,*adr1);
                  DEBUG_MSG("Decalage : %d ",dif);
                  if (dif!=0) return MAUVAIS_DECALAGE;
                  else 
                  {
                    *adr2 = temp_adr2;
                    return CMD_DISASM_OK_PLAGE;
                  }
                        
                }
            }
    else return ERREUR_SYNTAXE;
  }
return POSITION_IMPOSSIBLE;
}

/**
 * Affiche les messages d'erreur
 * @param verification : Variable donnant le type de l'erreur
 */

void erreur_fonction_disasm(int verification)
{
  switch(verification)
  {
    case ADRS_NON_HEXA3 : WARNING_MSG("ERROR [1] : Les adresses entrée ne sont pas hexadecimal ou désignent un emplacement non existant dans la memoire");break;
    case MAUVAIS_DECALAGE : WARNING_MSG("ERROR [15] : Les instruction MIPS sont dur 32 bits, le decalage entré est mauvais !");break;
    case ERREUR_SYNTAXE : WARNING_MSG("ERROR [16] : Mauvaise syntaxe ; utilisé un + pour un decalage ou : pour une plage  ");break; 
    case PAS_ADRESSE : WARNING_MSG("ERROR [17] : Vous n'avez pas entrez d'adresse !!!");break;
    case POSITION_IMPOSSIBLE : WARNING_MSG("ERREUR INCONNUE ; LE PROGRAMME SE TROUVE DANS UNE POSITION IMPOSSIBLE");break;
    case HORS_ZONE_TEXTE : WARNING_MSG("L'adresse que vous avez entrer n'est pas dans la zone de texte ou se trouve le code à desassambler");break;
    default : WARNING_MSG("ERREUR NON REFERENCE");
  }
}

/**
 * Fonction d'execution du desassamblage
 * @param adr1, adr2 ,decalage adresse des instructions a desassambler
 * @param mem memoire virtuelle
 * @param mrg tableau des registres
 * @param decalage_plage entier permettant de savoir si on a entré 2 adresses ou une adresse et un decalage
 */

int execute_cmd_disasm( uint32_t adr1 , uint32_t adr2 , int decalage, int decalage_plage, mem memoire,map_reg *  mrg)
{ definition dictionnaire;
  char f_name[64] = "dico_definitif.txt";
  dictionnaire = lecture_dictionnaire(f_name);
  uint32_t adr;
  uint32_t adr_2bis;
  union_RIJ union_struct;
  uint32_t target;

  switch(decalage_plage)
  {
    case CMD_DISASM_OK_PLAGE :
      adr_2bis=adr2;
      break;
    case CMD_DISASM_OK_DECALAGE :
     adr_2bis = adr1 | (uint32_t) decalage;
    break;
  }

DEBUG_MSG("ADRESSE DE DEBUT DE DESSASAMBLAGE : %08x",adr1);
DEBUG_MSG("ADRESSE DE FIN DU DESSASAMBLAGE : %08x",adr_2bis);

for(adr = adr1;adr<adr_2bis;adr=adr+4)
{ int sortie = 0;
  char * reg1=NULL;
  char * reg2=NULL;
  char * reg3=NULL;
  //DEBUG_MSG("ADR : %08x",adr);
  //affiche_mot(memoire,adr);
  uint32_t word;
  word = renvoi_mot (memoire,adr,mrg);
  //DEBUG_MSG("WORD : %u ",word);
  int k=0;
  int imm;
    while(k<42&&sortie==0)
    {
      if( (word&dictionnaire[k].masque) == dictionnaire[k].signature)
        {
            union_struct = return_operande(dictionnaire[k].type,word);
            printf("\n %04x :: %08x   %s",adr,word,dictionnaire[k].nom);
            switch(dictionnaire[k].type)
            {
              case 'R' :
                        switch(dictionnaire[k].nmbr_oper)
                        {
                          case 3 : if( strcmp(dictionnaire[k].op_mapping[0],"rs") == 0 && strcmp(dictionnaire[k].op_mapping[1],"rt") == 0 && strcmp(dictionnaire[k].op_mapping[2],"rd") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.r.rd);reg2 = convert_num_mnemonique(mrg,union_struct.r.rs);reg3 = convert_num_mnemonique(mrg,union_struct.r.rt);
                                      printf(" %s,%s,%s \n",reg1,reg2,reg3);sortie = 1;
                                    }
                                    else if ( strcmp(dictionnaire[k].op_mapping[0],"rt") == 0 && strcmp(dictionnaire[k].op_mapping[1],"rd") == 0 && strcmp(dictionnaire[k].op_mapping[2],"sa") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.r.rd);reg2 = convert_num_mnemonique(mrg,union_struct.r.rt);
                                      printf(" %s,%s,%u \n",reg1,reg2,union_struct.r.sa);sortie = 1;
                                    }
                                    break;
                          case 2 : if (strcmp(dictionnaire[k].op_mapping[0],"rt") == 0 && strcmp(dictionnaire[k].op_mapping[1],"rd") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.r.rd);reg2 = convert_num_mnemonique(mrg,union_struct.r.rs);
                                      printf(" %s,%s \n",reg1,reg2);sortie = 1;
                                    }
                                    else if (strcmp(dictionnaire[k].op_mapping[0],"rs") == 0 && strcmp(dictionnaire[k].op_mapping[1],"rt") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.r.rs);reg2 = convert_num_mnemonique(mrg,union_struct.r.rt);
                                      printf(" %s,%s \n",reg1,reg2);sortie = 1;
                                    }
                                    else if (strcmp(dictionnaire[k].op_mapping[0],"rs") == 0 && strcmp(dictionnaire[k].op_mapping[1],"hint") == 0)
                                    {
                                      printf(" $%u \n",union_struct.r.rs);sortie = 1;
                                    }
                                    break;
                          case 1 : if (strcmp(dictionnaire[k].op_mapping[0],"rd") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.r.rd);
                                      printf(" %s \n",reg1);sortie = 1;
                                    }
                                    else if (strcmp(dictionnaire[k].op_mapping[0],"code") == 0)
                                    {
                                      printf("\n");sortie = 1;
                                    }
                          case 0 : printf("\n");sortie = 1;break;

                          default :ERROR_MSG("FATAL ERROR : STRUCTURE DE LA COMMANDE NON TROUVEE"); 
                        }
              k++;
              break;
              case 'I' :
                        switch(dictionnaire[k].nmbr_oper)
                        {
                          case 3 : if( strcmp(dictionnaire[k].op_mapping[0],"rs") == 0 && strcmp(dictionnaire[k].op_mapping[1],"rt") == 0 && strcmp(dictionnaire[k].op_mapping[2],"immediate") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.i.rt);reg2 = convert_num_mnemonique(mrg,union_struct.i.rs);
                                      printf(" %s,%s,%d \n",reg1,reg2,union_struct.i.immediate);sortie = 1;
                                    }
                                    else if ( strcmp(dictionnaire[k].op_mapping[0],"base") == 0 && strcmp(dictionnaire[k].op_mapping[1],"rt") == 0 && strcmp(dictionnaire[k].op_mapping[2],"offset") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.i.rt);reg2 = convert_num_mnemonique(mrg,union_struct.i.rs);
                                      printf(" %s,0x%08x(%s) \n",reg1,union_struct.i.immediate,reg2);sortie = 1;
                                    }
                                    else if (strcmp(dictionnaire[k].op_mapping[0],"rs") == 0 && strcmp(dictionnaire[k].op_mapping[1],"rt") == 0 && strcmp(dictionnaire[k].op_mapping[2],"offset") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.i.rs);reg2 = convert_num_mnemonique(mrg,union_struct.i.rt);imm = union_struct.i.immediate*4;
                                      printf(" %s,%s,%d \n",reg1,reg2,imm);sortie = 1;
                                    }
                                    break;
                          case 2 : if (strcmp(dictionnaire[k].op_mapping[0],"rt") == 0 && strcmp(dictionnaire[k].op_mapping[1],"immediate") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.i.rt);
                                      printf(" %s,%u \n",reg1,union_struct.i.immediate);sortie = 1;
                                    }
                                    else if (strcmp(dictionnaire[k].op_mapping[0],"rs") == 0 && strcmp(dictionnaire[k].op_mapping[1],"offset") == 0)
                                    {
                                      reg1 = convert_num_mnemonique(mrg,union_struct.i.rs);
                                      printf(" %s,%u \n",reg1,union_struct.i.immediate);sortie = 1;
                                    }
                                    break;
                          default :ERROR_MSG("FATAL ERROR : STRUCTURE DE LA COMMANDE NON TROUVEE"); 
                        }
              k++;
              break;
              case 'J' :
              target = union_struct.j.target*4;
              printf(" 0x%08x \n",target);sortie = 1;
              k++;
              break;
              default : ERROR_MSG("FATAL ERROR : STRUCTURE DE LA COMMANDE NON TROUVEE");
            } 
        //printf("\n");   
            
        }    
      else k++;
    }
}

return 0;
}

/**
 * Retourne les valeurs des operandes du mot extrait du fichier elf,
 * @param type_struct indique le type d'instruction entré 
 * @param mot 32 bits extrait du fichier elf
 * @return le numero des registres ou les valeurs des immediate ou offset
 */

union_RIJ return_operande(char type_struct,uint32_t mot)
{   
    // Masque pour les structures de type R  
    uint32_t masque_rs =0x3E00000;
    uint32_t masque_rt = 0x1F0000;
    uint32_t masque_rd = 0xF800;
    uint32_t masque_sa = 0x7C0;

    // Masque pour les structures de type I
    int masque_immediate = 0xffff;

    //Masque pour les structures de type J
    uint32_t masque_target = 0x3ffffff;

    //initialisation de l'union a renvoyer
    union_RIJ uni;

    switch(type_struct)
    {
      case 'R' : 
      uni.r.rs = (mot & masque_rs) >> 21;
      uni.r.rt = (mot & masque_rt) >> 16;
      uni.r.rd = (mot & masque_rd) >> 11;
      uni.r.sa = (mot & masque_sa) >> 6;
      return uni;
      break;
      case 'I' :
      uni.i.rs = (mot & masque_rs) >> 21;
      uni.i.rt = (mot & masque_rt) >> 16;
      uni.i.immediate = (int) (mot & masque_immediate);
      return uni;
      break;
      case 'J' :
      uni.j.target = (mot & masque_target);
      return uni;
      default : ERROR_MSG("FATAL ERROR : STRUCTURE DE LA COMMANDE NON TROUVEE");
    }


}




























