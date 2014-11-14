#include "run.h"


int cmd_run(map_reg * mrg,mem memoire,interpreteur inter,liste lpb)
{
	if(memoire==NULL) return erreur_fonction_run(PAS_MEM);
	int retour;
	char * token;
	uint32_t PC;
	token = get_next_token(inter);
	DEBUG_MSG("input cmd_run : %s",token);
	uint32_t adr;
	uint32_t fin_code = memoire->seg->start._32 + memoire->seg->size._32;

	if(token == NULL) 
	{
		uint32_t PC_N = renvoi_reg_num(mrg,32);

		DEBUG_MSG("Pas d'adresse de depart entré , et PC = %08x",PC_N);
		
		if(PC_N==0) return erreur_fonction_run(PC_VIDE);

		else  
		{
			PC=PC_N;
			modif_reg_num(32,mrg,PC);
			definition dictionnaire_commande;
			char f_name[64] = "dico_definitif_2.txt";
			DEBUG_MSG("Lecture du dictionnaire c'est parti");
			dictionnaire_commande = lecture_dictionnaire(f_name);
			DEBUG_MSG("Lecture du dictionnaire c'est fini");
			retour = execute_cmd_run(mrg,memoire,lpb,dictionnaire_commande);
				if(retour==OK) return OK;
				else if (retour == DEHORS) return 0;
				else return erreur_fonction_run(PB);
		}
	}

	else sscanf(token,"%08x",&adr);



	if(is_hexa_v2(token)==0) {return erreur_fonction_run(NOT_HEXA);}

	else if (adr < 12288) return erreur_fonction_run(DEHORS_CODE);

	else if (adr > 16384) return erreur_fonction_run(DEHORS_CODE);

	else if (adr%4!=0) return erreur_fonction_run(DEBUT_INST);

	else if(adr>fin_code) return erreur_fonction_run(CODE_FINI);

	else 
	{
		sscanf(token,"%08x",&adr);
		PC=adr;
		modif_reg_num(32,mrg,PC);
		definition dictionnaire_commande;
		char f_name[64] = "dico_definitif.txt";
		DEBUG_MSG("Lecture du dictionnaire c'est parti");
  		dictionnaire_commande = lecture_dictionnaire(f_name);
  		DEBUG_MSG("Lecture du dictionnaire c'est fini");
			retour = execute_cmd_run(mrg,memoire,lpb,dictionnaire_commande);
				if(retour==OK) return OK;
				else if (retour == DEHORS) return 0;
				else return erreur_fonction_run(PB);
	}
return 0;}




int erreur_fonction_run(int verif)
{
	switch(verif)
	{
		case NOT_HEXA : WARNING_MSG("L'adresse que vous avez entrer n'est pas hexa !!");break;

		case DEHORS_CODE : WARNING_MSG("L'adresse entré est en dehors du code chargé en memoire");break;

		case DEBUT_INST : WARNING_MSG("L'adresse entré n'est pas au debut d'une instruction");break;

		case CODE_FINI : WARNING_MSG("L'adresse entré est à la fin du code chargé en memoire");break;

		case PB : WARNING_MSG("Il ya un pb lors de l'execution");break;

		case PAS_MEM : WARNING_MSG("Pas de programme chargé en memoire");break;

		case PC_VIDE : WARNING_MSG("Il n'a pas d'adresse dans le registre PC ; veuillez entré un adresse de debut d'execution");break;

		default : WARNING_MSG("Position impossible ");
	}
return 0;}




int execute_cmd_run(map_reg * mrg,mem memoire,liste l_BP,definition dictionnaire_commande)
{ 

//char *token;
FILE * fp2;
fp2 = stdin;
interpreteur inter2 = init_inter();
inter2->mode = INTERACTIF;
int erreur;
uint32_t fin_code = memoire->seg->start._32 + memoire->seg->size._32 ;
int BP_search;
//	int res;
int etat;
uint32_t PC = renvoi_reg_num(mrg,32);
uint32_t PC_r;
BP_search = rechercheBP(l_BP,PC);
				if(BP_search == 0) {etat = PAUSE;}
				else {etat = RUN;}

while(1)
{
	if(etat == NOT || etat == RUN || etat == TERM || etat ==ERREUR || etat == EXIT || acquire_line( fp2,  inter2)  == 0)
	{ 
//		while (etat != PAUSE || etat != NOT )
		{
			switch(etat)
			{
				case NOT : 
				DEBUG_MSG("\nNOT\n");
				//PC = PC +4;
            	//PC = renvoi_reg_num(mrg,32);
            	//modif_reg_num(32,mrg,PC);
            	BP_search = rechercheBP(l_BP,PC);
				if(BP_search == 0) {etat = PAUSE;break;}
				else {etat = RUN;break;}

				//}
				//else 
				//{
				//	etat = ERREUR;
				//	break;
				//} 
				//break;
				
				case RUN :
				DEBUG_MSG("\nRUN\n");
				if(PC==fin_code) etat = TERM;
				else
				{
					DEBUG_MSG("RUN : On commence :");
					instruction inst;
					inst = desassamble(mrg,memoire,inter2,PC,dictionnaire_commande);
					DEBUG_MSG("DESASSAMBLAGE TERMINEE");
					PC_r = renvoi_reg_num(mrg,32);
					if(PC==PC_r) PC = PC + 4;
					else PC = PC_r;
					modif_reg_num(32,mrg,PC);
					erreur = execut_instruction(mrg,memoire,inst);
					DEBUG_MSG("EXEXUTION TERMINEE");
					if(erreur != OK ) etat = EXIT;
					else etat = NOT;

				}
				break;

				case PAUSE : 
				DEBUG_MSG("PAUSE");
				char * token2 = get_next_token(inter2);
					if(token2==NULL) break;
					else if(strcmp(token2,"run")==0) {etat = RUN;}
					else if(PC==fin_code) etat = TERM;
					else if(strcmp(token2,"exit")==0) etat = EXIT ;
					else etat = ERREUR;
				break;

				case TERM : DEBUG_MSG("\nTERM\n"); return OK;
				break;
			
				case ERREUR : return ERREUR;
				break;
			
				case EXIT : exit( EXIT_SUCCESS );//return DEHORS;
				break;
			}
		}
	}
}
}

/**
 * Renvoie 0 si il y a un BP a l'adresse PC ; 1 sinon
 * @param : lbp : Liste des break point
 * PC : registre PC
 * return 0 ou 1
 */

int rechercheBP(liste lbp,uint32_t PC)
{
	liste l;
	int b;

	for(l=lbp;!est_vide(l);l=l->suiv)
	{
		if(l->val.adresse_BP == PC) return 0;

		else b = 1;
	}

return b;
}

instruction desassamble(map_reg * mrg,mem memoire,interpreteur inter,uint32_t PC,definition dictionnaire_commande)
{
	instruction inst;
	uint32_t word;
	word = renvoi_mot(memoire,PC);
	inst.def = recherche_dictionnaire(dictionnaire_commande,word);
	inst.operande = recherche_operande(dictionnaire_commande,word);

	return inst;
}


definition recherche_dictionnaire(definition dictionnaire_commande,uint32_t word)
{
	int k = 0;
	definition def_instruction=NULL;
	def_instruction=calloc(1,sizeof(*def_instruction));
	while(k<41)
		if( (word&dictionnaire_commande[k].masque) == dictionnaire_commande[k].signature)
		{
			DEBUG_MSG("NOM dicos : %s -- NUM FUNCTION : %d ",dictionnaire_commande[k].nom,dictionnaire_commande[k].num_function);
			strcpy(def_instruction->nom,dictionnaire_commande[k].nom);
			def_instruction->num_function = dictionnaire_commande[k].num_function;
			DEBUG_MSG("NOM extrait : %s -- NUM FUNCTION : %d ",def_instruction->nom,def_instruction->num_function);
			def_instruction->type = dictionnaire_commande[k].type;
			return def_instruction;
		}
		else k++;
return NULL;
}


union_RIJ recherche_operande(definition dictionnaire, uint32_t word)
{
	int k = 0;int sortie=0;
	union_RIJ union_struct;
	while(k<41&&sortie==0)
	{
		if( (word&dictionnaire[k].masque) == dictionnaire[k].signature)
		{
			union_struct=return_operande(dictionnaire[k].type,word);
			return union_struct;
		}
		else k++;
	}
return union_struct;
}



int execut_instruction(map_reg * mrg,mem memoire,instruction inst)
{
	DEBUG_MSG("On va executer l'instruction : %s",inst.def->nom);
	int retour = 0;
	int (*fonction_MIPS)(map_reg *,mem,union_RIJ);
	DEBUG_MSG("NUM FUNCTION : %d",inst.def->num_function);
	fonction_MIPS = choix_fonction(inst.def->num_function - 1); // A remplacer
	retour = (*fonction_MIPS)(mrg,memoire,inst.operande);
	if(retour == 1) return OK;
	else return 0;

return OK;}

//int (*listeFonctions[41])(map_reg *,mem,union_RIJ) = {ADD,ADDU,ADDI,ADDIU,SUB,SUBU,MULT,DIV,AND,ANDI,OR,ORI,XOR,SLL,SRL,SRA,SEB,SLT,SLTU,SLTI,SLTIU,LW,SW,LB,LBU,SB,LUI,MFHI,MFLO,BEQ,NOP,BNE,BGEZ,BGTZ,BLEZ,BLTZ,j,JAL,JR,BREAK,SYSCALL};
int (*listeFonctions[41])(map_reg *,mem,union_RIJ) = {NOP,ADD,ADDU,SUB,AND,OR,XOR,SLT,SLTU,SRL,SRA,SEB,MULT,DIV,JR,MFHI,MFLO,BREAK,SYSCALL,SLL,ADDI,ADDIU,ORI,SLTI,SLTIU,BEQ,ANDI,LW,SW,LB,LBU,SB,BNE,LUI,BGEZ,BGTZ,BLEZ,BLTZ,j,JAL};

int(* choix_fonction(int a))(map_reg *,mem,union_RIJ)
{
	return listeFonctions[a];
}


