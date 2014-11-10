#ifndef _fonction_mips_h
#define _fonction_mips_h

#include "run.h"

int add(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int addi(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int addiu(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int addu(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int And(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int andi(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int beq(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int bgez(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int bgtz(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int blez(map_reg * mrg,mem memoire,union_RIJ   union_struct);
int bltz(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int bne(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int Break(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int Div(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int j(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int jal(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int jalr(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int jr(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int lb(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int lbu(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int lui(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int lw(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int mfhi(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int mflo(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int mult(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int nop(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int Or(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int ori(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int sb(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int seb(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int sll(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int slt(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int slti(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int sltiu(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int sltu(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int sra(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int srl(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int sub(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int subu(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int sw(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int syscall(map_reg * mrg,mem memoire,union_RIJ  union_struct);
int Xor(map_reg * mrg,mem memoire,union_RIJ  union_struct);

int (*listeFonctions[41])(map_reg *,mem,union_RIJ) = {addi};




#endif