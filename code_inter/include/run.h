#ifndef _run_h
#define _run_h


#include "break_point.h"
#include "get_type_token.h"
#include "fonction_base.h"
#include "disasm_code.h"
#include "fonction_mips.h"

enum  {NOT_HEXA,DEHORS_CODE,DEBUT_INST,CODE_FINI,PB,NOT,RUN,PAUSE,TERM,OK,PAS_MEM,ERREUR,EXIT,DEHORS,PC_VIDE};



typedef struct {
	definition def;
	union_RIJ operande; 
}instruction;



int cmd_run(map_reg * mrg,mem memoire,interpreteur inter,liste lpb,stab symtab);
int erreur_fonction_run(int verif);
int execute_cmd_run(map_reg * mrg,mem memoire,liste l_BP,definition dictionnaire_commande,stab symtab);
int rechercheBP(liste lbp,uint32_t PC);
instruction desassamble(map_reg * mrg,mem memoire,interpreteur inter,uint32_t PC,definition dictionnaire_commande,stab symtab);
definition recherche_dictionnaire(definition dictionnaire_commande,uint32_t word);
union_RIJ recherche_operande(definition dictionnaire, uint32_t word);
int execut_instruction(map_reg * mrg,mem memoire,instruction inst);




int(*choix_fonction(int))(map_reg *,mem,union_RIJ);


//int (*listeFonctions[40])(union_RIJ,map_reg *,mem) = {ADD,ADDU,ADDI,ADDIU,SUB,SUBU,MULT,DIV,AND,ANDI,OR,ORI,XOR,SLL,SRL,SRA,SEB,SLT,SLTU,SLTI,SLTIU,LW,SW,LB,LBU,SB,LUI,MFHI,MFLO,BEQ,NOP,BNE,BGEZ,BGTZ,BLEZ,BLTZ,J,JAL,JR,BREAK,SYSCALL};




#endif