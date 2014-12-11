#include "set.h"

int cmd_set(interpreteur inter,mem memoire,map_reg * mrg)
{
    DEBUG_MSG("Chaine : %s", inter->input);
    int verif;
    int positon_registre;
    int res;
  	char * valeur=NULL;
    char * word=strdup("word");
    char * byte=strdup("byte");
    char * adresse=NULL;
    char * token=get_next_token(inter);
	DEBUG_MSG("TOKEN : %s", token);
    char** tab_all_reg=NULL;
    if( token!=NULL) 
    {
        if(strcmp(token,"mem")==0)
        {
        	token=get_next_token(inter);
            if(memoire==NULL) 
                {
                    WARNING_MSG("Pas de Programme chargé en memoire");
                    return 1;
                }
        	if(strcmp(token,"word")==0)
        		{
        			DEBUG_MSG("TEST DES ARGUMENTS DE LA FONCTION SET WORD");
        			verif=test_cmd_set(inter,word,&valeur,&adresse);  
        			if(verif==CMD_SET_WORD_OK) {res = execute_set_word(adresse,valeur,memoire,mrg);return CMD_OK_RETURN_VALUE;}
        			else  
                    {
                        erreur_cmd_set(verif);
                        return 1;
                    }
        		}
        	else if(strcmp(token,"byte")==0)
        		{
        			DEBUG_MSG("TEST DES ARGUMENT DE LA FONCTION SET BYTE"); 
        			verif=test_cmd_set(inter,byte,&valeur,&adresse);
                		if(verif==CMD_SET_BYTE_OK) {res = execute_set_byte(adresse,valeur,memoire,mrg);return CMD_OK_RETURN_VALUE;}
                    	else {erreur_cmd_set(verif);return 1;}
                }
            else WARNING_MSG(" Wrong argument given to command %s \n","set mem");
        }
        else if(strcmp(token,"reg")==0)
        {
        	DEBUG_MSG("TEST DES ARGUMENT DE LA FONCTION SET REG");
        	tab_all_reg=init_tab_registre(); 
		    token=get_next_token(inter);
		    DEBUG_MSG("REGISTRE ENTREE : %s",token);
                verif = test_cmd_set_reg(inter,tab_all_reg,token,&valeur,&positon_registre);
                if(verif==CMD_SET_REG_OK) {res=execute_set_reg(token,valeur,mrg,positon_registre);return CMD_OK_RETURN_VALUE;}
                else {erreur_cmd_set(verif);return 1;}
        }
    }
    else
    {
        WARNING_MSG("No Argument is given to %s command \n","set");
        return 1;
    }
return 1;}


int test_cmd_set(interpreteur inter,char * wb,char ** value,char ** adr)
{  DEBUG_MSG("DEBUT de la commande de TEST d'SET %s",wb);
    char * token = get_next_token(inter);
	DEBUG_MSG("TOKEN ENTREE : %s",token);
    if(token==NULL) return PAS_DADRESSE_ENTREE2;
	
	else if(is_hexa_v2(token)!=0) 
		{
			*adr=strdup(token);
        	token=get_next_token(inter);
        	DEBUG_MSG("ADRS RECONNUE PASSONS A LA VALEUR : %s",token);
				if(token==NULL) return PAS_VALEUR_A_TESTER;
        		else *value=strdup(token);
        }
      
	else return ADRS_NON_HEXA2;

    if(strcmp(wb,"byte")==0) return CMD_SET_BYTE_OK;

    else if(strcmp(wb,"word")==0) return CMD_SET_WORD_OK;
    
    else return CMD_SET_UK;
    

return 1;
}



int test_cmd_set_reg(interpreteur inter,char ** tab_tout_reg,char * reg1,char ** value,int * position)
{ 
int a;
        INFO_MSG("INPUT test_cmd_SET_reg : %s",reg1);

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
        return CMD_SET_REG_OK;
        }

    }   
    
    else    return REGI_NON_EXISTANT;


return ERROR;
}

int execute_set_word(char * adr,char * val, mem memoire,map_reg * mrg)
{ DEBUG_MSG("VALEUR A tester : %s à l'adresse %s ",val,adr);
    if(is_word_byte(val)==WORD)
    {
        INFO_MSG("SET WORLD à l'adresse %s par la valeur %s",adr,val);
        uint32_t adresse;
        uint32_t valeur;
        uint32_t val_mem;
        sscanf(adr,"%08x",&adresse);
        sscanf(val,"%08x",&valeur); // Valeur est modifié pas sscanf ! pkoi ?
        set_word (memoire,adresse,valeur,mrg);
    }

	else WARNING_MSG("ERROR [30] : VALEUR DONNEE NON WORD");
return 0;}



int execute_set_byte(char * adr,char * val,mem memoire,map_reg * mrg)
{   if(is_word_byte(val)==BYTE)
    {
        INFO_MSG("SET BYTE à l'adresse %s par la valeur %s",adr,val);
        uint32_t adresse;
        uint32_t valeur;
        sscanf(adr,"%08x",&adresse);
        sscanf(val,"%08x",&valeur);
        DEBUG_MSG("adresse : %08x ",adresse);
        uint32_t val_mem = renvoi_byte(memoire,adresse,NULL);
        	set_byte (memoire,adresse,valeur,mrg);
    }
	else 
    {
        WARNING_MSG("VALEUR DONNEE NON BYTE");
        return 0;
    }
return 0;}

int execute_set_reg(char * reg1,char * value, map_reg * mrg,int position_reg)
{
    INFO_MSG("SET REG = %s VALEUR = %s ",reg1,value);
    int numero;
    uint32_t valeur_reg;
    sscanf(value,"%x",&valeur_reg);
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
	modif_reg_num(numero,mrg,valeur_reg);
return 0;}

void erreur_cmd_set(verif)
{ switch(verif)
    {
    case ADRS_NON_HEXA2 : WARNING_MSG(" ERROR [1] : Les adresses entrée ne sont pas hexadecimal ou désignent un emplacement non existant dans la memoire"); break;

    case REGI_NON_EXISTANT : WARNING_MSG(" ERROR [2] : Les registres que vous avez indiqué n'existe pas, verifiez que vous avez taper $ avant le nom ou le numero du registre !"); break;

    case ERROR_i : WARNING_MSG(" ERROR [3] : La fonction assert se trouve dans un emplacement impossible, une erreur a été oublié");break;

    case PAS_DADRESSE_ENTREE2 : WARNING_MSG("ERROR [4] : Vous n'avez pas entré d'adresse !!!!"); break;

    case NO_VALUE_REG : WARNING_MSG("ERROR [6] : PAS DE REGISTRE ENTREE");break;

    case NO_TYPE_VALUE : WARNING_MSG("ERROR [7] : Valeur entrer non reconnue");break;

    case PAS_VALEUR_A_TESTER : WARNING_MSG("ERROR[8] : IL n'y a pas de valeur a tester !!!!");break;

    case CMD_SET_UK : WARNING_MSG("ERROR [9] : Unknow type of identifier");break;

    default: WARNING_MSG("ERREUR NON REFERENCE");
}

}
