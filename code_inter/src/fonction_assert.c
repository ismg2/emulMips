#include "fonction_assert.h"


/**
 * fonction d'execution de la fonction ASSERT d'un mot de 32 bits
 * @param  adr adresse de valeur a tester
 * @param  val valeur a tester
 * @return     pour le moment il ne retourne qu'un message verifiant que les parametres sont bon
 */
int execute_assert_word(char * adr,char * val, mem memoire)
{ DEBUG_MSG("VALEUR A tester : %s à l'adresse %s ",val,adr);
    if(is_word_byte(val)==WORD)
    {
        INFO_MSG("ASSERT WORLD à l'adresse %s par la valeur %s",adr,val);
        uint32_t adresse;
        uint32_t valeur;
        uint32_t val_mem;
        sscanf(adr,"%08x",&adresse);
        sscanf(val,"%08x",&valeur); // Valeur est modifié pas sscanf ! pkoi ?
        val_mem = renvoi_mot(memoire,adresse,NULL);
        DEBUG_MSG("VAL_MEMOIRE : %08x ; VALEUR DONNEE PAR L'UTILISATEUR : %08x ",val_mem,valeur);
        if(val_mem == valeur) 
        {
            INFO_MSG("Bravo c'est la bonne Valeur");
            return 0;
        }
        else 
        {
            INFO_MSG("Dommage ce n'est pas la bonne valeur en memoire");
            return 1;
        }

    }

	else WARNING_MSG("ERROR [30] : VALEUR DONNEE NON WORD");
return 1;}

/**
 * fonction d'execution de la fonction ASSERT d'un mot de 8 bits
 * @param  adr adresse de valeur a tester
 * @param  val valeur a tester
 * @return     pour le moment il ne retourne qu'un message verifiant que les parametres sont bon
 */

int execute_assert_byte(char * adr,char * val,mem memoire)
{   if(is_word_byte(val)==BYTE)
    {
        INFO_MSG("ASSERT BYTE à l'adresse %s par la valeur %s",adr,val);
        uint32_t adresse;
        uint32_t valeur;
        sscanf(adr,"%08x",&adresse);
        sscanf(val,"%08x",&valeur);
        DEBUG_MSG("adresse : %08x ",adresse);
        uint32_t val_mem = renvoi_byte(memoire,adresse,NULL);
        if(val_mem == valeur) 
        {
            INFO_MSG("Bravo c'est la bonne Valeur");
            return 0;
        }
        else 
        {
            INFO_MSG("Dommage ce n'est pas la bonne valeur en memoire");
            return 1;
        }
    }
	else 
    {
        WARNING_MSG("VALEUR DONNEE NON BYTE");
        return 0;
    }
return 0;}

/**
 * fonction d'execution de la fonction ASSERT d'un registre
 * @param  reg1 nom du registre a tester
 * @param  value valeur a tester
 * @return     pour le moment il ne retourne qu'un message verifiant que les parametres sont bon
 */



int execute_assert_reg(char * reg1,char * value, map_reg * mrg,int position_reg)
{
    INFO_MSG("ASSERT REG = %s VALEUR = %s ",reg1,value);
    int numero;
    uint32_t valeur_reg;
    char * numero_registre;
    int type = get_type(value);

   // switch(type)
   // {
        //case HEXA : 
        sscanf(value+2,"%08x",&valeur_reg);
       // break;

     //   case DECIMAL : sscanf(*value,"%u",&valeur_reg);break;

     //   default : WARNING_MSG("TYPE VARIABLE INDEFINI");return 1;
   // }

    DEBUG_MSG("position_reg : %d",position_reg);
    if(position_reg >=35)
    {
        numero = convert_mnemo_num(mrg,reg1);
    }
    else 
    {
        sscanf(reg1+1,"%d",&numero);
    }

    DEBUG_MSG("NUMERO REGISTRE : %d VALEUR REG : %08x",numero,valeur_reg);

    if(mrg[numero]->valeur==valeur_reg)
    {
        INFO_MSG("BRAVO !!! C'est la bonne Valeur !!");
        return 0;
    }
    else
    {
        INFO_MSG("Dommage mais ce n'est pas la bonne valeur");
        return 1;
    }

}

/**
 * Test si les argument entré dans l'interpreteur sont bon
 * @param  inter sturcture d'interpreteur
 * @param  wb indique si test un mot de 32 bit ou un byte de 8 bits
 * @param  value valleur à tester
 * @param  adr adresse du mot/byte a tester
 * @return un entier indiquant une erreur ou un entier indiquant que les parametres entrés dans l'interpreteur sont bon 
 */



int test_cmd_assert(interpreteur inter,char * wb,char ** value,char ** adr)
{  DEBUG_MSG("DEBUT de la commande de TEST d'assert %s",wb);
    char * token = get_next_token(inter);
	DEBUG_MSG("TOKEN ENTREE : %s",token);
    if(token==NULL) return PAS_DADRESSE_ENTREE;
	
	else if(is_hexa_v2(token)!=0) 
    	{*adr=strdup(token);
        token=get_next_token(inter);
	           DEBUG_MSG("ADRS RECONNUE PASSONS A LA VALEUR : %s",token);
		if(token==NULL) return PAS_VALEUR_A_TESTER;
        else *value=strdup(token);
        }
      
	else return ADRS_NON_HEXA2;

    if(strcmp(wb,"byte")==0) return CMD_ASSERT_BYTE_OK;

    else if(strcmp(wb,"word")==0) return CMD_ASSERT_WORD_OK;
    
    

return 1;
}

/**
 * Gestion des erreurs
 * @param verif entier indiquant quels erreurs s'est produites
 * @return Retour le message d'erreur
 */


void erreur_cmd_assert(verif)
{ switch(verif)
    {
    case ADRS_NON_HEXA2 : WARNING_MSG(" ERROR [1] : Les adresses entrée ne sont pas hexadecimal ou désignent un emplacement non existant dans la memoire"); break;

    case REGI_NON_EXISTANT : WARNING_MSG(" ERROR [2] : Les registres que vous avez indiqué n'existe pas, verifiez que vous avez taper $ avant le nom ou le numero du registre !"); break;

    case ERROR_i : WARNING_MSG(" ERROR [3] : La fonction assert se trouve dans un emplacement impossible, une erreur a été oublié");break;

    case PAS_DADRESSE_ENTREE : WARNING_MSG("ERROR [4] : Vous n'avez pas entré d'adresse !!!!"); break;

    case DEUX_POINT_MANQUANT : WARNING_MSG("ERROR [5] : Verifiez si vous n'avez pas oublier les deux points ou que certaines adresses sont manquantes, ILS SONT ESSENTIEL");break;

    case NO_VALUE_REG : WARNING_MSG("ERROR [6] : PAS DE REGISTRE ENTREE");break;

    case NO_TYPE_VALUE : WARNING_MSG("ERROR [7] : Valeur entrer non reconnue");break;

    case PAS_VALEUR_A_TESTER : WARNING_MSG("ERROR[8] : IL n'y a pas de valeur a tester !!!!");break;

    default: WARNING_MSG("ERREUR NON REFERENCE");
}

}

/**
 * Test si les commande pour tester les valeurs d'un registre sont bonnes
 * @param inter interpreteur
 * @param tab_tout_reg tableau contenant tout les registres
 * @param reg1 registre a tester
 * @param value valeur a tester
 */

int test_cmd_assert_reg(interpreteur inter,char ** tab_tout_reg,char * reg1,char ** value,int * position)
{ 
//   int i=0;
int a;
        INFO_MSG("INPUT test_cmd_ASSERT_reg : %s",reg1);

    if(reg1==NULL) return NO_VALUE_REG;
        
   else if(reg_exist(reg1,tab_tout_reg,&a)==0)  
    {  
        *value = get_next_token(inter);
        *position = a;
        DEBUG_MSG("Valeur à tester : %s",*value);
        if(*value==NULL)
        {
        return PAS_VALEUR_A_TESTER;
        }
        else 
        {
        return CMD_ASSERT_REG_OK;
        }

    }   
    
    else    return REGI_NON_EXISTANT;


return ERROR;
}

/**
 * Programme principale gerant l'appel a la fonction assert 
 */

int cmd_assert(interpreteur inter,mem memoire,map_reg * mrg) 
{
    DEBUG_MSG("Chaine : %s", inter->input);
    int verif;
    int positon_registre;
  	char * valeur=NULL;
    char * word=strdup("word");
    char * byte=strdup("byte");
    char * adresse=NULL;
    char * token=get_next_token(inter);
	DEBUG_MSG("TOKEN : %s", token);
    char** tab_all_reg=NULL;
    if( token!=NULL) 
    {
        if(strcmp(token,"word")==0)
        {       DEBUG_MSG("TEST DES ARGUMENTS DE LA FONCTION ASSERT WORD");
              verif=test_cmd_assert(inter,word,&valeur,&adresse);  
              if(verif==CMD_ASSERT_WORD_OK) return execute_assert_word(adresse,valeur,memoire);
              else  erreur_cmd_assert(verif);
        }
            
            
        else if(strcmp(token,"reg")==0)
        {   DEBUG_MSG("TEST DES ARGUMENT DE LA FONCTION ASSERT REG"); 
            tab_all_reg=init_tab_registre();
		    token=get_next_token(inter);
		    DEBUG_MSG("REGISTRE ENTREE : %s",token);
                verif = test_cmd_assert_reg(inter,tab_all_reg,token,&valeur,&positon_registre);
                if(verif==CMD_ASSERT_REG_OK) return execute_assert_reg(token,valeur,mrg,positon_registre);
                else erreur_cmd_assert(verif);
                
        }
        else if(strcmp(token,"byte")==0)
        {    DEBUG_MSG("TEST DES ARGUMENT DE LA FONCTION ASSERT BYTE"); 
                verif=test_cmd_assert(inter,byte,&valeur,&adresse);
                if(verif==CMD_ASSERT_BYTE_OK) return execute_assert_byte(adresse,valeur,memoire);
                    else erreur_cmd_assert(verif);
        }
        

        else
        {  
        WARNING_MSG(" Wrong argument given to command %s \n","assert");
        return 1;
        }    
        
    }

    else
    {
        WARNING_MSG("No Argument is given to %s command \n","assert");
        return 1;
    }

return 400;}







