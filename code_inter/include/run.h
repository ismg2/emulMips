#ifndef _run_h
#define _run_h


#include "break_point.h"
#include "get_type_token.h"
#include "fonction_base.h"
#include "disasm_code.h"

enum  {NOT_HEXA,DEHORS_CODE,DEBUT_INST,CODE_FINI,PB,NOT,RUN,PAUSE,TERM,OK,PAS_MEM,ERREUR,EXIT,DEHORS};


//NOT = NOT TERMINATED

typedef struct {
	definition def;
	union_RIJ operande; 

//	int *
}instruction;



int cmd_run(map_reg * mrg,mem memoire,interpreteur inter,liste lpb);
int erreur_fonction_run(int verif);
int execute_cmd_run(map_reg * mrg,mem memoire,uint32_t PC,liste l_BP,definition dictionnaire_commande);
int rechercheBP(liste lbp,uint32_t PC);
instruction desassamble(map_reg * mrg,mem memoire,interpreteur inter,uint32_t PC,definition dictionnaire_commande);
definition recherche_dictionnaire(definition dictionnaire_commande,uint32_t word);
union_RIJ recherche_operande(definition dictionnaire, uint32_t word);
int execut_instruction(map_reg * mrg,mem memoire,instruction inst);

//declaration des prototypes des fonctions du MIPS



int(*(choix_fonction(int)))(map_reg *,mem,union_RIJ);


// Declaration du tableau de fonction
//int (*listeFonctions[41])(union_RIJ,map_reg *,mem) = {add,addi,addiu,addu,And,andi,beq,bgez,bgtz,blez,bltz,bne,Break,Div,j,jal,jalr,jr,lb,lbu,lui,lw,mfhi,mflo,mult,nop,Or,ori,sb,seb,sll,slt,slti,sltiu,sltu,sra,srl,sub,subu,sw,syscall,Xor};






#endif