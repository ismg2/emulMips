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

/*
Renvoie 0 si les lettres de chaine sont A B .. F ou a b ... f ou des chiffres de 0 à 9
              1 sinon  
*/

int lettre_hexa(char * chaine)
{ int i=2; int erreur=0;

do    
       { 
		switch(chaine[i]) {
			case 'a' :i++; break;
			case 'b' :i++; break;
			case 'c' :i++; break;
			case 'd' :i++; break;
			case 'e' :i++; break;
			case 'f' :i++; break;
			case 'A' :i++; break;
			case 'B' :i++; break;
			case 'C' :i++; break;
			case 'D' :i++; break;
			case 'E' :i++; break;
			case 'F' :i++; break;
			case '0' :i++; break;
			case '1' :i++; break;
			case '2' :i++; break;
			case '3' :i++; break;
			case '4' :i++; break;
			case '5' :i++; break;
			case '6' :i++; break;
			case '7' :i++; break;
			case '8' :i++; break;
			case '9' :i++; break;
			default : erreur=1; }
        }
        while(erreur==0&&i<strlen(chaine));
return erreur;
}

//retourne 0 si non hexa un nombre positif sinon

int is_hexa_v2(char* chaine) {    int i; 
            int resultat=0;
if(chaine!=NULL  &&  strlen(chaine)>2  && chaine[0]=='0' && chaine[1]=='x' && sscanf(chaine,"%x",&i)==1 && lettre_hexa(chaine)==0 && strlen(chaine)<11)
     resultat=1;
     else resultat=0;
		 
return resultat;}

// retourne 0 si tout les chiffres sont des 0 ou des 1

int is_bit(char * chaine)
{int i=0;int erreur=0;
	while( i<strlen(chaine) && erreur==0 )   
	{
		if( chaine[i]=='0' || chaine[i]=='1' )
		{
			i++;	
		}
		else erreur=1;
	}
return erreur;}
//retourne 0 si non BYTE un nombre positif sinon

int is_byte(char* chaine) {   
            int resultat=0;int taille_ad=0;int type=0;
	type=get_type(chaine);
	{ switch(type)
		{
		case HEXA : taille_ad=4;break;
		case DECIMAL : taille_ad=16;break;
		default : return 0;
		}
	}

if(chaine!=NULL  &&  strlen(chaine)==taille_ad && is_bit(chaine)!=0)
     resultat=1;
     else resultat=0;
		 
return resultat;}

//retourne 0 si non WORD un nombre positif sinon

int is_word(char* chaine) 
{    int resultat;int taille_ad;int type;
	type=get_type(chaine);
	{ switch(type)
		{
		case HEXA : taille_ad=6;break;
		case DECIMAL : taille_ad=32;break;
		default : return 0;
		}
	}
	
	if(chaine!=NULL  &&  strlen(chaine)==taille_ad && is_bit(chaine)!=0) resultat=1;
        else resultat=0;
		 
return resultat;}






// retourne 1 si un des chiffres est plus grand que 8


int inf_8(char* chaine)
{
	int i=0;int erreur=0;int valeur1;
	
	while(erreur==0&&i<strlen(chaine))
		{ sscanf(&chaine[i],"%d",&valeur1);
		if((valeur1)<=8&&(valeur1)>=0) i++;
		else erreur=1; 
		}
return erreur;}

//retourne 0 si non octal un nombre positif sinon

int is_octal(char * chaine)

{int erreur;
	if(chaine!=NULL  && chaine[0]=='0' && inf_8(chaine)==0 && strlen(chaine)>1)
		erreur = 1;
	else erreur =0;
return erreur;}

// retourne la taille de l'adresse donné
// ou 

int taille(char* chaine)
{	int i,compteur=0;
	if(is_hexa_v2(chaine)==0) return CMD_UNKOWN_RETURN_VALUE;
	else for(i=2;i<strlen(chaine);i++) compteur++;
	return compteur;
}


// retourne 1 si decimal, 0 si non is_decimal

int is_decimal(char* chaine)
{int i=0;
int dec=0;
int erreur=0;
	while(erreur==0&&i<strlen(chaine))
	{	sscanf(&chaine[i],"%d",&dec);
		switch(dec)
			{
			case 0 : i++; break;  
			case 1 : i++;break;  
			case 2 : i++;break;  
			case 3 : i++;break;  
			case 4 : i++;break;  
			case 5 : i++;break;  
			case 6 : i++;break;  
			case 7 : i++;break;  
			case 8 : i++;break;  
			case 9 : i++;break;  
			case '-' : i++;break;
			default : erreur=1;
			}
	}
return erreur;}

// Fonction qui affiche tout les registres demandé , une fois qu'aucune erreur n'a été detecté

void execute_disp_reg(interpreteur inter,char ** tab_reg_demm,int verification)
{int i ;
  switch(verification)
  {
  case CMD_DISP_REG_OK : DEBUG_MSG("AFFICHAGE d'une liste de registre");
                            INFO_MSG("VOICI LES REGISTRES QUE L'ON VA AFFICHER :");
                            for (i = 0; i < 70; i++)
                            {
                               if(strcmp(tab_reg_demm[i],"")!=0) INFO_MSG(" %s ",tab_reg_demm[i]);
                            }
                             break;

  case CMD_DISP_REG_ALL_OK : INFO_MSG("ON AFFICHE TOUT "); break;

  case CMD_DISP_MEM_PLAGE_OK : INFO_MSG("VOICI LA PLAGE QUE L'ON VA AFFICHER :");
                            for (i = 0; i < 70; i++)
                            {
                                INFO_MSG(" %s ",tab_reg_demm[i]);
                            }
                            break;
    default : WARNING_MSG("POSITION IMPOSSIBLE");
    }

}

// Retourne 0 si les registres existent 1 sinon

int reg_exist(char * reg1,char ** tab_tout_reg)
{ int j=0;int erreur=1;
    while(j<69&&erreur!=0)
                    {
                        if(strcmp(reg1,tab_tout_reg[j])==0)  erreur=0;
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
    strcpy(tab_compar[34],"$33");                    strcpy(tab_compar[69],"$PC");
//aff(tab_compar,70);
return tab_compar;
}


// Verifie si apres disp  et mem les token entrée sont bien une plage avec des adresses hexa
// ou si on demande d'afficher la map


int test_cmd_dispmem(interpreteur inter,char * adr1,char * adr2)
{
    adr1=get_next_token(inter);
    char * two_point=get_next_token(inter);
    adr2=get_next_token(inter);
    int verif=0;
    DEBUG_MSG("adresse analysed test_cmd_dispmem function  '%s'   '%s' ",adr1,adr2);
    DEBUG_MSG("LES FAMEUX DEUX POINT '%s' ",two_point);
    int deux_point=cherche_deux_point(two_point);
    if (adr1==NULL||adr2==NULL) return verif = PAS_DADRESSE_ENTREE;
        else if (strcmp(adr1,"map")==0) return verif = CMD_DISP_MEM_MAP_OK; 

            else if (is_hexa_v2(adr1)==0 || is_hexa_v2(adr2)==0) return verif = ADRS_NON_HEXA;
            else if (deux_point==1) return verif = DEUX_POINT_MANQUANT;
            
    else return verif = CMD_DISP_MEM_PLAGE_OK;
}

//Execute la commande d'affichage d'une plage d'adresse ou de toute la map
// si map = CMD_DISP_MEM_MAP_OK  on affiche toute la map , sinon juste entre adr1 et adr2 


void execute_disp_mem(char * adr1,char * adr2,int map)
{
	switch(map)
	{
		case CMD_DISP_MEM_PLAGE_OK : DEBUG_MSG("On affiche la plage de registre entre %s et %s",adr1,adr2);break;
		case CMD_DISP_MEM_MAP_OK : DEBUG_MSG("ON AFFICHE LA MAP DE MEMOIRE");
//						print_mem;
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



int test_cmd_dispreg(interpreteur inter,char ** tab_tout_reg,char ** tab_reg_commander)
{ 
   char * token=get_next_token(inter);
   char * two_point;
   
   int i=0;
        INFO_MSG("INPUT test_cmd_dispreg : %s",token);
        //INFO_MSG("TWO POINTS  : %s",two_point);


    if(token==NULL) return NO_VALUE_REG;
        
   else if(strcmp(token,"all")==0) return CMD_DISP_REG_ALL_OK;

   else if(cherche_deux_point((two_point=get_next_token(inter)))==0)
   {
        char * token2=get_next_token(inter);
            DEBUG_MSG(" REGISTRE entré sont : %s %s",token,token2);
                
        if(reg_exist(token,tab_tout_reg)==1 || reg_exist(token2,tab_tout_reg)==1 ) return REG_NON_EXISTANT;

             
        else {  strcpy(tab_reg_commander[0],token);
                strcpy(tab_reg_commander[1],token2);
                return CMD_DISP_REG_PLAGE_OK;
            }
   }


   else if(reg_exist(token,tab_tout_reg)==0)  
    {   DEBUG_MSG("TOKEN : '%s' ",token);
        while(token != NULL && !reg_exist(token,tab_tout_reg))
       { 
            
            DEBUG_MSG("TOKEN BOUCLE : %s",token);
            if (reg_exist(token, tab_tout_reg)==0)
            {
                tab_reg_commander[i]=strdup(token);
            }
            else 
            {
                return REG_NON_EXISTANT;
            }

            token = get_next_token(inter);
            printf("%p\n", &token); // l'adresse du prochain token est NULL, ce n'est pas normal !!!!!
            i++;
        }
        
        return CMD_DISP_REG_OK;
    }   
    else    return REG_NON_EXISTANT;


return ERROR;
}


int cmd_disp(interpreteur inter) 
{
    DEBUG_MSG("Chaine : %s", inter->input);
    int verif;
    char * token=NULL;
    char * adresse1=NULL;
    char * adresse2=NULL;
    char** tab_all_reg=NULL;
    char** tab_reg_dem=NULL;
    if((token = get_next_token(inter))!=NULL) 
    {
            
        
        
        if(strcmp(token,"mem")==0)
        {  
            verif = test_cmd_dispmem(inter,adresse1,adresse2);
            switch(verif)
            {
                case CMD_DISP_MEM_PLAGE_OK :
                        execute_disp_mem(adresse1,adresse2,CMD_DISP_MEM_PLAGE_OK);
                    break;

                case CMD_DISP_MEM_MAP_OK :
                        execute_disp_mem(adresse1,adresse2,CMD_DISP_MEM_MAP_OK);
                    break;

                default : erreur_cmd_disp(verif);
                    break;
            }
            
        }    
        else if(strcmp(token,"reg")==0)
        {   DEBUG_MSG("Debut du traitement de la demande d'affichage des registres"); 
            tab_all_reg=init_tab_registre();
            tab_reg_dem=init_matrice();
                verif = test_cmd_dispreg(inter,tab_all_reg,tab_reg_dem);
                switch(verif)
                {
                case CMD_DISP_REG_OK : execute_disp_reg(inter,tab_reg_dem,CMD_DISP_REG_OK);break;
                case CMD_DISP_REG_ALL_OK : execute_disp_reg(inter,tab_reg_dem,CMD_DISP_REG_ALL_OK);break;
                case CMD_DISP_REG_PLAGE_OK :execute_disp_reg(inter,tab_reg_dem,CMD_DISP_REG_PLAGE_OK);break;
                   
                default : erreur_cmd_disp(verif);break;
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

return 400;}


void cmd_load(interpreteur inter)
{
    printf("Commande non executer");
}

void aff(char **m, int b)
{int j;
    for(j=0;j<b;j++)
    {printf(" %s     " ,m[j]);}
}










