#ifndef _fonction_mips_h
#define _fonction_mips_h

#include "registre.h"
#include "mem.h"
#include "disasm_code.h"

#define MOF 0x80000000


int appartenance_gpr(int rd, map_reg * map);

int ADD(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int ADDI(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int ADDIU(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int ADDU(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int AND(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int ANDI(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int BEQ(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int BGEZ(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int BGTZ(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int BLEZ(map_reg * mrg,mem memoire,union_RIJ   union_struct);
int BLTZ(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int BNE(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int BREAK(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int DIV(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int j(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int JAL(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int JALR(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int JR(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int LB(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int LBU(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int LUI(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int LW(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int MFHI(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int MFLO(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int MULT(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int NOP(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int OR(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int ORI(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SB(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SEB(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SLL(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SLT(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SLTI(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SLTIU(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SLTU(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SRA(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SRL(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SUB(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SUBU(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SW(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int SYSCALL(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int XOR(map_reg * mrg,mem memoire,union_RIJ  union_struct);


//int (*listeFonctions[40])(union_RIJ,map_reg *,mem) = {ADD,ADDU,ADDI,ADDIU,SUB,SUBU,MULT,DIV,AND,ANDI,OR,ORI,XOR,SLL,SRL,SRA,SEB,SLT,SLTU,SLTI,SLTIU,LW,SW,LB,LBU,SB,LUI,MFHI,MFLO,BEQ,NOP,BNE,BGEZ,BGTZ,BLEZ,BLTZ,j,JAL,JR,BREAK,SYSCALL};




//int (*listeFonctions[41])(union_RIJ,map_reg *,mem) = {add,addi,addiu,addu,And,andi,beq,bgez,bgtz,blez,bltz,bne,Break,Div,j,jal,jalr,jr,lb,lbu,lui,lw,mfhi,mflo,mult,nop,Or,ori,sb,seb,sll,slt,slti,sltiu,sltu,sra,srl,sub,subu,sw,syscall,Xor};

//int (*listeFonctions[40])(union_RIJ,map_reg *,mem) = {ADD,ADDU,ADDI,ADDIU,SUB,SUBU,MULT,DIV,AND,ANDI,OR,ORI,XOR,SLL,SRL,SRA,SEB,SLT,SLTU,SLTI,SLTIU,LW,SW,LB,LBU,SB,LUI,MFHI,MFLO,BEQ,NOP,BNE,BGEZ,BGTZ,BLEZ,BLTZ,J,JAL,JR,BREAK,SYSCALL};

#endif