#include "get_type_token.h"

/**
 * retourne le type du token (fonction très incomplete)
 * @param chaine le token à analyser
 * @return un entier correspondant au type du token
 * 
 */
int get_type(char* chaine) {
	if(chaine==NULL) { return UNKNOWN;}
    else if (is_hexa_v2(chaine)!=0)
        	return HEXA;
    else if(is_binary(chaine)!=0)
			return BINAIRE;
    else if(is_decimal(chaine)!=0)
        	return DECIMAL;
   else return UNKNOWN;
}
//retourne 0 si non BYTE or WORD et le type de variable sinon
int is_word_byte(char* chaine) {   
  int type=0;
	type=get_type(chaine);
	{ switch(type)
		{
		case HEXA : if(strlen(chaine+2)==2) return BYTE;
					else if(strlen(chaine+2)==4) return WORD;
						else return 0;break;
		case BINAIRE : if(strlen(chaine)==8) return BYTE;
						else if(strlen(chaine)==16) return WORD;
						else return 0;break;
		default : return 0;
		}
	}

return 400;}


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

// retourne 1 si tout les chiffres sont des 0 ou des 1 : BINAIRE

int is_binary(char * chaine)
{int i=0;int erreur=1;
	while( i<strlen(chaine) && erreur==1 )   
	{
		if( chaine[i]=='0' || chaine[i]=='1' )
		{
			i++;	
		}
		else erreur=0;
	}
return erreur;}

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
