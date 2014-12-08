#include "break_point.h"

/**
 * Fonction de gestion d'erreur liés au break point
 * @param verification entier donnant le type d'erreur
 * @return On affiche le message d'erreur et on retourne 0
 */

int erreur_fonction_break_point( int verification)
{
	switch(verification)
	{
		case PAS_ADR : WARNING_MSG("ERROR [18] : Vous n'avez pas entré l'adresse du Break Point");break;

		case NO_ARGS : WARNING_MSG("ERROR [19] : Pas d'argument entré");break;

		case PAS_DECALAGE : WARNING_MSG("ERROR [20] : Vous n'avez pas entré de decalage");break;

		case CARAC_U : WARNING_MSG("ERROR [21] : Caractère entré non reconnue par la nomenclature du MIPS");break;

		case NON_HEXA : WARNING_MSG("ERROR [22] : ADRESSE ENTREE NON HEXA");break;

		case PAS_LOAD : WARNING_MSG("ERROR [23] : PAS de programme chargé en memoire ");break;

		case HORS_CODE : WARNING_MSG("ERROR [24] : Votre Break Point est à l'exterieur de la zone de code");break;

		case BP_EXISTANT : WARNING_MSG("ERROR [25] : Break point existant !!");break;

		case POSITION_IMPOS : WARNING_MSG("POSITION IMPOSSIBLE");break;

		case BP_NON_EXIST : WARNING_MSG("Le break point que vous voulez supprimez n'existe pas !");break;

		case PAS_BP : WARNING_MSG("Pas de break Point a supprimer");break;

		case PAS_INST : WARNING_MSG("L'adresse entré ne se trouve pas au debut d'une instruction");break;

		default : WARNING_MSG("Erreur non réferencé");
	}
return 0;}

/**
 * execute la commande d'ajout ou de suppression ou d'affichage d'un break point ou renvoie vers la fonction d'erreur si problème
 * @param  memoire  Memoire du microprocesseur
 * @param  inter    interpreteur
 * @param  l_breakP liste de Break POint
 * @return          1 si la commande est executer avec succes, 0 si erreur
 */
int cmd_break(mem memoire, interpreteur inter, liste * l_breakP)
{
	char * token = get_next_token(inter);
	char * adr=NULL;
	int retour=0;
	DEBUG_MSG("INPUT cmd_break : %s",token);

	if (token == NULL) return erreur_fonction_break_point(NO_ARGS);

	if(memoire==NULL) return erreur_fonction_break_point(PAS_LOAD);

	else if(strcmp(token,"add")==0)
	{	
		adr = get_next_token(inter);
		if(adr==NULL) return erreur_fonction_break_point(PAS_ADR);
		while(adr!=NULL)
		{	
			retour = execute_add_BP(adr,l_breakP,memoire);
			adr = get_next_token(inter);
		}
		*l_breakP=ranger_ordre_croissant(*l_breakP);
	}

	else if(strcmp(token,"del")==0)
	{
		adr = get_next_token(inter);
		if(adr==NULL) return erreur_fonction_break_point(PAS_ADR);

		else if(strcmp(adr,"all") == 0 )
		{
			retour = execute_del_BP("NULL",l_breakP,DEL_ALL);
		}
		else 
		{
			while(adr!=NULL)
			{
				retour = execute_del_BP(adr,l_breakP,DEL_1);
				adr = get_next_token(inter);
			}
			
		}  
	}

	else if(strcmp(token,"list")==0)
	{
		visualiser_liste(*l_breakP);
	}
	else return erreur_fonction_break_point(CARAC_U);

//return retour;
return CMD_OK_RETURN_VALUE;}

/**
 * Ajout d'un break point à la liste de break point
 * @param adresse adresse ou l'on doit rajouter le break point
 * @param l_breakP liste des break point
 * @param memoire Memoire du microprocesseur
 * @return 0 si il y a une erreur 1 si succes
 */



int execute_add_BP(char * adresse,liste * l_breakP,mem memoire)
{	uint32_t adr;
	BP break_p;
	int verif;
	if(is_hexa_v2(adresse)==0) return erreur_fonction_break_point(NON_HEXA);

	else if(memoire == NULL) return erreur_fonction_break_point(PAS_LOAD);

	else
	{
		uint32_t fin_code = memoire->seg->start._32 + memoire->seg->size._32 ;
		sscanf(adresse,"%08x",&adr);
		DEBUG_MSG("Lim inf : %u -- adresse : %u -- Lim ext : %u",START_MEM,adr,START_MEM + 0x1000);

		if(adr < START_MEM) return erreur_fonction_break_point(HORS_CODE);

		else if(adr >= START_MEM + 0x1000) return erreur_fonction_break_point(HORS_CODE);

		else if (adr%4!=0) return erreur_fonction_break_point(PAS_INST);

		else //(adr >= 12288 && adr < 16384)
		{
			if(adr > fin_code) {INFO_MSG("Le Break point est à la fin du code");}
			break_p.adresse_BP = adr;
			verif = bp_already_here(break_p,*l_breakP);
			DEBUG_MSG("BP_EXISTANT : 11 BP_EXISTE_PAS : 12 /// verif : %d",verif);
			if(verif==BP_EXISTE_PAS)
			{
				*l_breakP = ajout_tete(break_p,*l_breakP);
				DEBUG_MSG("BREAK POINT AJOUTÉE");
			}
			else if (verif==BP_EXISTANT )
			{
				return erreur_fonction_break_point(BP_EXISTANT);
			}
			else return erreur_fonction_break_point(POSITION_IMPOS);
		}

	} 
return CMD_OK_RETURN_VALUE;
}

/**
 * Suppression d'un break point à la liste de break point
 * @param adresse adresse ou l'on doit rajouter le break point
 * @param l_breakP liste des break point
 * @param ToR indicateur qui peut valoir DEL_ALL dans ce cas on supprime tout les BP ou DELL_1 et on supprime qu'un seul BP
 * @return 0 si il y a une erreur 1 si succes
 */



int execute_del_BP(char * adresse,liste * l_breakP,int ToR)
{
	liste p;
	uint32_t adr;
	sscanf(adresse,"%08x",&adr);
	DEBUG_MSG(" adr = 0x%s -- DEL_ALL = 4  DEL_1 = 5 et on a %d ",adresse,ToR);
	if (ToR == DEL_ALL)
	{
		if(*l_breakP==NULL) return erreur_fonction_break_point(PAS_BP);
		while(*l_breakP!=NULL) 
			{
				*l_breakP =  supprimer_tete(*l_breakP);
				//visualiser_liste(*l_breakP); 
				
			}
			return 1;
	}

	else if (ToR == DEL_1)
	{
		p=*l_breakP;
		//int i=0;
		//while(p!=NULL && p->val.adresse_BP!=adr) {p=p->suiv;i++;}
		if(p!=NULL) 
			{
				*l_breakP=supprimen(adr,*l_breakP);
				//DEBUG_MSG("BP SUPPRIMER");
				return 1;
			}
		else return erreur_fonction_break_point(BP_NON_EXIST);
	}
return erreur_fonction_break_point(POSITION_IMPOS);
}


/**
 * Verifie si à l'adresse entré il n'y a pas deja de BP
 * @param break_p structure contenant l'adresse du BP à tester
 * @param l_breakP liste des break point
 * @return BP_EXISTE_PAS si le BP n'existe pas ou BP_EXISTANT si BP existe
 */

int bp_already_here(BP break_p,liste lBP)
{
	liste p=lBP;
	int retour=BP_EXISTE_PAS;
	while(p!=NULL && p->val.adresse_BP!=break_p.adresse_BP)
	{
		p=p->suiv;
		retour = BP_EXISTE_PAS;
	}
	if(p!=NULL) {retour = BP_EXISTANT;}

return retour;}


/**
 * Renvoie l'adresse la plus petite de la liste
 * @param l liste de BP
 * @return le BP dont l'adresse est la plus petite
 */

BP cherche_plus_petit(liste l)
{
	BP petit;
	petit.adresse_BP=0x90000000;
	liste p=l;

	while(p!=NULL) 
	{
		if(petit.adresse_BP > p->val.adresse_BP )
		{
			petit.adresse_BP = p->val.adresse_BP;
		}
		else p=p->suiv;
	}
return petit;	
}






/**
 * Range la liste des BP dans l'ordre croissant de leur adresse
 * @param l liste de break point non ordonné
 * @return liste de break point ordonné
 */

liste ranger_ordre_croissant(liste l)
{
	BP petite;
	liste liste_ordonne=creer_liste();

	if(l==NULL) return NULL;

	else if(l->suiv == NULL) return l;

	else
	{
		while(l!=NULL)
		{

			petite = cherche_plus_petit(l);
			liste_ordonne = ajout_queue(petite,liste_ordonne);
			l=supprimen(petite.adresse_BP,l);
		}
	}
return liste_ordonne;
}












