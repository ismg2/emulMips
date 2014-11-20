//#include "aide_fonctions.h"

#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include "common/registre.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t signature;
    uint32_t masque;
    char nom[64];
    char type;
    char * op_mapping[64];
    int nmbr_oper;
} *definition;


typedef struct {
    definition def;
    char* op1;
    char* op2;
    char* op3;
    char* op4;
    //int (*f);
} instruction;

int appartenance_gpr(int rd, map_reg * map);
long int convert_long(char* operateur);
void execute_next_instruction(map_reg * map);
void ADD	(instruction inst, map_reg * map);
void ADDI	(instruction inst, map_reg * map);
void ADDIU	(instruction inst, map_reg * map);
void ADDU	(instruction inst, map_reg * map);
void AND	(instruction inst, map_reg * map);
void ANDI	(instruction inst, map_reg * map);
void BEQ	(instruction inst, map_reg * map);
void BGEZ	(instruction inst, map_reg * map);
void BGTZ	(instruction inst, map_reg * map);
void BLEZ	(instruction inst, map_reg * map);
void BLTZ	(instruction inst, map_reg * map);
void BNE	(instruction inst, map_reg * map);
void DIV	(instruction inst, map_reg * map);
void J		(instruction inst, map_reg * map);
void JAL	(instruction inst, map_reg * map);
void JALR	(instruction inst, map_reg * map);
void JR		(instruction inst, map_reg * map);
void LUI	(instruction inst, map_reg * map);
void MFHI	(instruction inst, map_reg * map);
void MFLO	(instruction inst, map_reg * map);
void MULT	(instruction inst, map_reg * map);
void NOP	(instruction inst, map_reg * map);
void OR		(instruction inst, map_reg * map);
void ORI	(instruction inst, map_reg * map);
void SEB	(instruction inst, map_reg * map);
void SLL	(instruction inst, map_reg * map);
void SLT	(instruction inst, map_reg * map);
void SLTI	(instruction inst, map_reg * map);
void SLTIU	(instruction inst, map_reg * map);
void SLTU	(instruction inst, map_reg * map);
void SRA	(instruction inst, map_reg * map);
void SRL	(instruction inst, map_reg * map);
void SUB 	(instruction inst, map_reg * map);
void SUBU 	(instruction inst, map_reg * map);
void XOR	(instruction inst, map_reg * map);



#ifdef __cplusplus
}
#endif

#endif /* _MEM_H_ */
