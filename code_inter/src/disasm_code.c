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
        for (int i = 0; i < def[j].nmbr_oper ; i++)
          { token=strtok(NULL,"   ");
            char * tempo = calloc(2,sizeof(*tempo));
            sscanf(token,"%s",tempo);
            def[j].op_mapping[i]=strdup(tempo);
            //printf("\t OPERANDE numero %d : %s\n",i+1,def[j].op_mapping[i]);
          }
      }
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

int cmd_disasm(interpreteur inter,mem  memoire)
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
        return execute_cmd_disasm(adresse1,adresse2,deca,CMD_DISASM_OK_PLAGE,memoire);
        //return 0;
    break;

    case CMD_DISASM_OK_DECALAGE : 
        DEBUG_MSG("CMD_DISASM_OK_DECALAGE");
        DEBUG_MSG(" LA PLAGE A AFFICHER %08x + %d ",adresse1,deca);
        return execute_cmd_disasm(adresse1,adresse2,deca,CMD_DISASM_OK_DECALAGE,memoire);
        break;
    
    default : erreur_fonction_disasm(verif);
  }

return 1;
}



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
                  unsigned int dif = (temp_adr2-*adr1)%4;
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
    default : WARNING_MSG("ERREUR NON REFERENCE");
  }
}

int execute_cmd_disasm( uint32_t adr1 , uint32_t adr2 , int decalage, int decalage_plage, mem memoire)
{ definition dictionnaire;
  char f_name[64] = "dico_definitif.txt";
  dictionnaire = lecture_dictionnaire(f_name);
  uint32_t adr;
  uint32_t adr_2bis;
  union_RIJ union_struct;
  switch(decalage_plage)
  {
    case CMD_DISASM_OK_PLAGE :
      for(adr = adr1;adr<=adr2;adr=adr+4)
      {
        affiche_mot(memoire,adr);
      }
      break;
    case CMD_DISASM_OK_DECALAGE :
      adr_2bis = adr1+decalage;
      for(adr = adr1;adr<adr_2bis;adr=adr+4)
      {
        //DEBUG_MSG("ADR : %08x",adr);
        //affiche_mot(memoire,adr);
        uint32_t word = renvoi_mot (memoire,adr);
        //DEBUG_MSG("WORD : %u ",word);
        int k=0;
        while(k<41)
        {
          if( (word&dictionnaire[k].masque) == dictionnaire[k].signature)
          {
            union_struct = return_operande(dictionnaire[k].type,word);
            switch(dictionnaire[k].type)
            {
              case 'R' :
              printf(" %04x :: %08x   %s $%u,$%u,$%u \n",adr,word,dictionnaire[k].nom,union_struct.r.rd,union_struct.r.rs,union_struct.r.rt);
              k++;
              break;
              case 'I' :
              printf(" %04x :: %08x   %s $%u,$%u,%u \n",adr,word,dictionnaire[k].nom,union_struct.i.rt,union_struct.i.rs,union_struct.i.immediate);
              k++;
              break;
              case 'J' :
              printf(" %04x :: %08x   %s %u \n",adr,word,dictionnaire[k].nom,union_struct.j.target);
              k++;
              break;
              default : ERROR_MSG("FATAL ERROR : STRUCTURE DE LA COMMANDE NON TROUVEE");
            }
            
          }
          else k++;
        }
      } 
      break;
  }

return 0;}

union_RIJ return_operande(char type_struct,uint32_t mot)
{   
    // Masque pour les structures de type R  
    uint32_t masque_rs =0x3E00000;
    uint32_t masque_rt = 0x1F0000;
    uint32_t masque_rd = 0xF800;
    uint32_t masque_sa = 0x7C0;

    // Masque pour les structures de type I
    uint32_t masque_immediate = 0xffff;

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
      return uni;
      break;
      case 'I' :
      uni.i.rs = (mot & masque_rs) >> 21;
      uni.i.rt = (mot & masque_rt) >> 16;
      uni.i.immediate = (mot & masque_immediate);
      return uni;
      break;
      case 'J' :
      uni.j.target = (mot & masque_target);
      return uni;
      default : ERROR_MSG("FATAL ERROR : STRUCTURE DE LA COMMANDE NON TROUVEE");
    }


}




























