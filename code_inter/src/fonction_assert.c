
#include "fonction_assert.h"



int execute_assert_word(char * adr,char * val)
{ DEBUG_MSG("VALEUR A tester : %s à l'adresse %s ",val,adr);
    if(is_word_byte(val)==WORD)
INFO_MSG("ASSERT WORLD à l'adresse %s par la valeur %s",adr,val);
	else WARNING_MSG("VALEUR DONNEE NON WORD");
return 0;}

int execute_assert_byte(char * adr,char * val)
{   if(is_word_byte(val)==BYTE)
     INFO_MSG("ASSERT BYTE à l'adresse %s par la valeur %s",adr,val);
	else WARNING_MSG("VALEUR DONNEE NON BYTE");
return 0;}

int execute_assert_reg(char * reg1,char ** value)
{
    INFO_MSG("ASSERT REG = %s VALEUR = %s ",reg1,*value);
return 0;}



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



// Gere les messages d'erreur ppour la fonction 


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




int test_cmd_assert_reg(interpreteur inter,char ** tab_tout_reg,char * reg1,char ** value)
{ 
//   int i=0;
        INFO_MSG("INPUT test_cmd_ASSERT_reg : %s",reg1);

    if(reg1==NULL) return NO_VALUE_REG;
        
   else if(reg_exist(reg1,tab_tout_reg)==0)  
    {  
        *value = get_next_token(inter);
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



int cmd_assert(interpreteur inter) 
{
    DEBUG_MSG("Chaine : %s", inter->input);
    int verif;
  	char * valeur=NULL;
char * word=strdup("word");
char * byte=strdup("byte");
char * adresse=NULL;
    char * token=get_next_token(inter);
	DEBUG_MSG("INTER INPUT : %s", inter->input);
	DEBUG_MSG("TOKEN : %s", token);
    char** tab_all_reg=NULL;
    if( token!=NULL) 
    {
        if(strcmp(token,"word")==0)
        {       DEBUG_MSG("TEST DES ARGUMENTS DE LA FONCTION ASSERT WORD");
              verif=test_cmd_assert(inter,word,&valeur,&adresse);  
              if(verif==CMD_ASSERT_WORD_OK) return execute_assert_word(adresse,valeur);
              else  erreur_cmd_assert(verif);
        }
            
            
        else if(strcmp(token,"reg")==0)
        {   DEBUG_MSG("TEST DES ARGUMENT DE LA FONCTION ASSERT REG"); 
            tab_all_reg=init_tab_registre();
		token=get_next_token(inter);
		DEBUG_MSG("REGISTRE ENTREE : %s",token);
                verif = test_cmd_assert_reg(inter,tab_all_reg,token,&valeur);
                if(verif==CMD_ASSERT_REG_OK) return execute_assert_reg(token,&valeur);
                    else    erreur_cmd_assert(verif);
                
        }
        else if(strcmp(token,"byte")==0)
        {    DEBUG_MSG("TEST DES ARGUMENT DE LA FONCTION ASSERT BYTE"); 
            verif=test_cmd_assert(inter,byte,&valeur,&adresse);
                if(verif==CMD_ASSERT_BYTE_OK) return execute_assert_byte(adresse,valeur);
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







