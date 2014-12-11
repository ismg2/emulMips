#include "run.h"

/**
 * Algorithme general de l'excution du code entré dans la zone .text
 * @param  mrg     map reggistre
 * @param  memoire memoire virtuelle
 * @param  inter   interpreteur
 * @param  lpb     liste des Break Point
 * @return         1 si succes 0 sinon
 */
int cmd_run(map_reg * mrg,mem memoire,interpreteur inter,liste lpb,stab symtab)
{
	if(memoire==NULL) return erreur_fonction_run(PAS_MEM);
	int retour;
	char * token;
	uint32_t PC;
	token = get_next_token(inter);
	char * token2 = get_next_token(inter);
	if(token2!=NULL) {WARNING_MSG("Too much Argument");return 1;}
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
			char f_name[64] = "dictionnaire.txt";
			DEBUG_MSG("Lecture du dictionnaire c'est parti");
			dictionnaire_commande = lecture_dictionnaire(f_name);
			DEBUG_MSG("Lecture du dictionnaire c'est fini");
			retour = execute_cmd_run(mrg,memoire,lpb,dictionnaire_commande,symtab);
				if(retour==OK) return OK;
				else if (retour == DEHORS) return 0;
				else return erreur_fonction_run(PB);
		}
	}

	else sscanf(token,"%08x",&adr);



	if(is_hexa_v2(token)==0) {return erreur_fonction_run(NOT_HEXA);}

	else if (adr < START_MEM) return erreur_fonction_run(DEHORS_CODE);

	else if (adr > START_MEM + 0x1000) return erreur_fonction_run(DEHORS_CODE);

	else if (adr%4!=0) return erreur_fonction_run(DEBUT_INST);

	else if(adr>fin_code) return erreur_fonction_run(CODE_FINI);

	else 
	{
		sscanf(token,"%08x",&adr);
		PC=adr;
		modif_reg_num(32,mrg,PC);
		definition dictionnaire_commande;
		char f_name[64] = "dictionnaire.txt";
		DEBUG_MSG("Lecture du dictionnaire c'est parti");
  		dictionnaire_commande = lecture_dictionnaire(f_name);
  		DEBUG_MSG("Lecture du dictionnaire c'est fini");
			retour = execute_cmd_run(mrg,memoire,lpb,dictionnaire_commande,symtab);
				if(retour==OK) return 0;
				else if (retour == DEHORS) return 0;
				else return erreur_fonction_run(PB);
	}
//return 0;
return CMD_OK_RETURN_VALUE;}

/**
 * Gestion des erreurs
 * @param verif entier indiquant l'erreur
 * @return retourn le message d'erreur puis 0
 */


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

/**
 * Machine a état lors de l'execution
 * @param  mrg     map reggistre
 * @param  memoire memoire virtuelle
 * @param  inter   interpreteur
 * @param  lpb     liste des Break Point
 * @param dictionnaire_commande dictionnaire contenant tout les commandes du Mips
 */


int execute_cmd_run(map_reg * mrg,mem memoire,liste l_BP,definition dictionnaire_commande,stab symtab)
{ 

//char *token;
FILE * fp2;
fp2 = stdin;
interpreteur inter2 = init_inter();
inter2->mode = INTERACTIF;
int erreur;
uint32_t fin_code = memoire->seg[3].start._32 + memoire->seg[3].size._32 ;
int BP_search;
instruction inst;
int etat;
int pause_step=0;
uint32_t ra;
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
            	BP_search = rechercheBP(l_BP,PC);
				if(BP_search == 0) {etat = PAUSE;}
				else if(PC==fin_code) {etat = TERM;}
				else {etat = RUN;break;}
				break;

				case RUN :
				DEBUG_MSG("\nRUN\n");
				{
					DEBUG_MSG("RUN : On commence :");
					inst = desassamble(mrg,memoire,inter2,PC,dictionnaire_commande,symtab);
					DEBUG_MSG("DESASSAMBLAGE TERMINEE");
					PC_r = renvoi_reg_num(mrg,32);
					if(PC==PC_r) PC = PC + 4;
					else PC = PC_r;
					modif_reg_num(32,mrg,PC);

					erreur = execut_instruction(mrg,memoire,inst);
					DEBUG_MSG("EXEXUTION TERMINEE");
					if(erreur == 400 ) etat = EXIT;
					else if(PC==fin_code) {etat = TERM;}
					else if(erreur == PAUSE) {etat = PAUSE;}
					else if(pause_step==1) {etat = PAUSE;}
					/*else if(pause_step == 2) // On continue a executer tout le sous programme
					{
						DEBUG_MSG("Execution de l'ensemble du sous programme");
						ra = renvoi_reg_num(mrg,31);
						while(PC != fin_code && PC!=ra && erreur ==0)
						{
							inst = desassamble(mrg,memoire,inter2,PC,dictionnaire_commande,symtab);
							DEBUG_MSG("DESASSAMBLAGE TERMINEE");
							PC_r = renvoi_reg_num(mrg,32);
							if(PC==PC_r) PC = PC + 4;
							else PC = PC_r;
							modif_reg_num(32,mrg,PC);
							erreur = execut_instruction(mrg,memoire,inst);
							DEBUG_MSG("EXEXUTION TERMINEE");
						}

						if(PC == ra) etat = PAUSE;

						else if(erreur == 0) etat=EXIT;

						else etat = NOT;
					}*/

					else if(erreur == OK) etat = NOT;

					else etat=NOT;

				}
				break;

				case PAUSE : 
				DEBUG_MSG("PAUSE");
				char * token2 = get_next_token(inter2);
					if(token2==NULL) break;
					else if(strcmp(token2,"run")==0) {etat = RUN;pause_step=0;}
					else if(PC==fin_code) etat = TERM;
					else if(strcmp(token2,"exit")==0) etat = EXIT ;
					else if(strcmp(token2,"step")==0) 
					{
						etat = RUN; pause_step = 1;
						/*char * token3 = get_next_token(inter2);
						inst = desassamble(mrg,memoire,inter2,PC,dictionnaire_commande,symtab);
						if(token3 == NULL)
						{
							
							if(inst.def->type == 'J') {pause_step = 2;etat = RUN;}
							else {etat = RUN;pause_step = 1;}
						}
						else if(strcmp(token3,"into")==0)
						{
							etat = RUN;
							pause_step = 1;	
						}
							pause_step=1;
							etat = RUN;*/
					}
					else etat = ERREUR;
				break;

				case TERM : DEBUG_MSG("\nTERM\n"); return OK;
				break;
			
				case ERREUR : WARNING_MSG("MAUVAISE COMMANDE");etat = PAUSE;//return ERREUR;
				break;
			
				case EXIT : //exit( EXIT_SUCCESS );
				return DEHORS;
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

/**
 * Desassamblage de l'instruction a executer (ou afficher)
 * @param  mrg     map reggistre
 * @param  memoire memoire virtuelle
 * @param  inter   interpreteur
 * @param  lpb     liste des Break Point
 * @param dictionnaire_commande dictionnaire contenant tout les commandes du Mips
 */

instruction desassamble(map_reg * mrg,mem memoire,interpreteur inter,uint32_t PC,definition dictionnaire_commande,stab symtab)
{
	instruction inst;
	uint32_t word;
	word = renvoi_mot(memoire,PC,mrg);
	inst.def = recherche_dictionnaire(dictionnaire_commande,word);
	inst.operande = recherche_operande(dictionnaire_commande,word);
	int resu = execute_cmd_disasm(PC,PC+4,0,0,memoire,mrg,symtab);

	return inst;
}

/**
 * Recherche dans le dico l'instruction à retourne
 * @param  mrg     map reggistre
 * @param word mot extrait du fichier elf à l'adresse PC
 * @param dictionnaire_commande dictionnaire contenant tout les commandes du Mips
 * @return les differentes elements d'une instruction
 */

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

/**
 * Recherche dans le dico l'instruction à retourne
 * @param word mot extrait du fichier elf à l'adresse PC
 * @param dictionnaire_commande dictionnaire contenant tout les commandes du Mips
 * @return les operandes de l'instruction
 */


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

/**
 * Execut l'instruction par l'appel au pointeur de fontion de l'instruction
 */

int execut_instruction(map_reg * mrg,mem memoire,instruction inst)
{
	DEBUG_MSG("On va executer l'instruction : %s",inst.def->nom);
	int retour = 0;
	int (*fonction_MIPS)(map_reg *,mem,union_RIJ);
	DEBUG_MSG("NUM FUNCTION : %d",inst.def->num_function);
	fonction_MIPS = choix_fonction(inst.def->num_function - 1); // A remplacer
	retour = (*fonction_MIPS)(mrg,memoire,inst.operande);
	if(retour == 1) return OK;
	else if(retour == 2) return PAUSE;
	else return 400;

return OK;}

// Declaration du tableau de pointeur
int (*listeFonctions[43])(map_reg *,mem,union_RIJ) = {NOP,ADD,ADDU,SUB,AND,OR,XOR,SLT,SLTU,SRL,SRA,SEB,MULT,DIV,JR,MFHI,MFLO,BREAK,SYSCALL,ADDI,ADDIU,ORI,SLTI,SLTIU,BEQ,ANDI,LW,SW,LB,LBU,SB,BNE,LUI,BGEZ,BGTZ,BLEZ,BLTZ,j,JAL,JALR,SUBU,SLL};

// On entre le numero de l'instruction tiré du desassamblage et on retourne le pointeurs de cette fonctions
int(* choix_fonction(int a))(map_reg *,mem,union_RIJ)
{
	return listeFonctions[a];
}


//Desassamble une instruction et une seul 








