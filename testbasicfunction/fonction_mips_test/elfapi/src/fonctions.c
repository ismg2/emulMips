#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "fonctions.h"
#include "common/registre.h"
#include "common/notify.h"

/////////////////////////////////////////
/// Fonctions aidant aux instructions ///
/////////////////////////////////////////

int appartenance_gpr(int rd, map_reg * map) {
    int a;
    if(rd>34 || rd<0) {
        a=1;
        return a;
    }
    else if(rd>23 || rd<8) {
        a=2;
        return a;
    }
    else {
        a=0;
        return 0;
    }
}

long int convert_long(char* operateur){
    long int valeur;
	sscanf(operateur,"%ld",&valeur);
	return valeur;
}

void execute_next_instruction(map_reg * map){
	return;
}

/////////////////////////////////////////
///            Instructions           ///
/////////////////////////////////////////


void ADD (instruction inst, map_reg * map){
    uint32_t temp;
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op3);
    int a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        temp=map[rs]->valeur + map[rt]->valeur;
        if( ((map[rs]->valeur)<0) & ((map[rt]->valeur)<0) & (temp>0) ) {
            WARNING_MSG("IntegerOverflow");
            return;
        }
        else if( ((map[rs]->valeur)>0) & ((map[rt]->valeur)>0) & (temp<0) ) {
            WARNING_MSG("IntegerOverflow");
            return;
        }
        else{
            modif_reg_num(rd, map, temp);
            return;
        }
    }
    return;
}

void ADDI (instruction inst, map_reg * map){
    long temp;
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    long int immediate=convert_long(inst.op3);
    int a;
    a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }                                                                                                                                                           
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }                                                                                                                           
    else{                                                                                                       
        temp=(map[rs]->valeur) + immediate;
        if( ((map[rs]->valeur)<0) & ((map[rd]->valeur)<0) & (temp>0) ) {
            WARNING_MSG("IntegerOverflow");
            return;
        }
        else if ( ((map[rs]->valeur)>0) & ((map[rd]->valeur)>0) & (temp<0) ) {
            WARNING_MSG("IntegerOverflow");
            return;
        }
        else{
        	modif_reg_num(rd, map, temp);
        	return;
        }                                                                
    }	
    return;
}

void ADDIU (instruction inst, map_reg * map){
    long temp;
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    long int immediate=convert_long(inst.op3);
    int a;
    a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }                                                                                                                                                           
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }                                                                                                                           
    else{
        temp=(map[rs]->valeur) + immediate;
        modif_reg_num(rd, map, temp);
        return;
    }                                                                                                                
}

void ADDU (instruction inst, map_reg * map){
    uint32_t temp;
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op3);
    int a;
    a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        temp=(map[rs]->valeur)+(map[rt]->valeur);
        modif_reg_num(rd, map, temp);     
        return;   
    }
}

void AND (instruction inst, map_reg * map) {
    uint32_t temp;
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op3);
    int a;
    a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        temp=(map[rs]->valeur) & (map[rt]->valeur);
        modif_reg_num(rd, map, temp);
        return;
    }
}

void ANDI (instruction inst, map_reg * map) {
    long temp;
    long int immediate=convert_long(inst.op3);
    int rs=convert_mnemo_num(map, inst.op2);
    int rd=convert_mnemo_num(map, inst.op1);
    int a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        temp=(map[rs]->valeur)&immediate;
        modif_reg_num(rd, map, temp);
        return;
    }
}

void BEQ(instruction inst, map_reg * map){
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op1);
    long int offset= convert_long(inst.op3) << 2;
    int result;
    execute_next_instruction(map);
    if(rs==rt){
        result=(map[32]->valeur)+1+offset;
        modif_reg_num(32, map, result);
        return;
    }
    else{
        result=(map[32]->valeur)+1;
        modif_reg_num(32, map, result);
        return;
    }
}

void BGEZ(instruction inst, map_reg * map){
    int rs=convert_mnemo_num(map, inst.op1);
    long int offset= convert_long(inst.op3) << 2;
    int result;
    execute_next_instruction(map);
    if(rs>=0){
        result=(map[32]->valeur)+1+offset;
        modif_reg_num(32, map, result);
        return;
    }
    else{
        result=(map[32]->valeur)+1;
        modif_reg_num(32, map, result);
        return;
    }
}

void BGTZ(instruction inst, map_reg * map){
    int rs=convert_mnemo_num(map, inst.op1);
    long int offset= convert_long(inst.op3) << 2 ;
    int result;
    execute_next_instruction(map);
    if(rs>=0){
        result=(map[32]->valeur)+1+offset;
        modif_reg_num(32, map, result);
        return;
    }
    else{
        result=(map[32]->valeur)+1;
        modif_reg_num(32, map, result);
        return;
    }
}

void BLEZ(instruction inst, map_reg * map){
    int rs=convert_mnemo_num(map, inst.op1);
    long int offset= convert_long(inst.op2) << 2;
    int result;
    execute_next_instruction(map);    
    if(rs<=0){
        result=(map[32]->valeur)+1+offset;
        modif_reg_num(32, map, result);
        return;
    }
    else{
        result=(map[32]->valeur)+1;
        modif_reg_num(32, map, result);
        return;
    }
}

void BLTZ(instruction inst, map_reg * map){
    int rs=convert_mnemo_num(map, inst.op1);
    long int offset= convert_long(inst.op3) << 2;
    int result;
    execute_next_instruction(map);    
    if(rs<0){
        result=(map[32]->valeur)+1+offset;
        modif_reg_num(32, map, result);
        return;
    }
    else{
        result=(map[32]->valeur)+1;
        modif_reg_num(32, map, result);
        return;
    }
}

void BNE(instruction inst, map_reg * map){
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op1);
    long int offset= convert_long(inst.op3) << 2;
    int result;
    execute_next_instruction(map);    
    if(rs!=rt){
        result=(map[32]->valeur)+1+offset;
        modif_reg_num(32, map, result);
        return;
    }
    else{
        result=(map[32]->valeur)+1;
        modif_reg_num(32, map, result);
        return;
    }
}

void DIV(instruction inst, map_reg * map){
    int rs=convert_mnemo_num(map, inst.op1);
    int rt=convert_mnemo_num(map, inst.op2);
    long int q = (map[rs]->valeur) / (map[rt]->valeur);
    long int r = (map[rs]->valeur)%(map[rt]->valeur);
    modif_reg_num(33, map, q);
    modif_reg_num(34, map, r);
    return;
}

void J(instruction inst, map_reg * map) {
    long int target=convert_long(inst.op1)<<2;
    execute_next_instruction(map);
    modif_reg_num(32, map, target);
}

void JAL(instruction inst, map_reg * map){
    long int target=convert_long(inst.op1)<<2;
    int GRP31=(map[32]->valeur)+8;
    modif_reg_num(31, map, GRP31);
    execute_next_instruction(map);
    modif_reg_num(32, map, target);  
}

// Non terminée
/*
void JALR(instruction inst, map_reg map){
    if(inst.op2==NULL){
        int rs=convert_mnemo_num(map, inst.op1);
        int rd=31; 
    }
    else{
        int rs=convert_mnemo_num(map, inst.op2);
        int rd=convert_mnemo_num(map, inst.op1);
    }
    long int temp=*((map+rs)->pointeur);
    long int GRPrd=*((map+32)->pointeur)+8;
    modif_reg_num(rd, map, GRPrd);
    execute_next_instruction();
    return;
}

// Non terminée
void JR(instruction inst, map_reg map){
    int rs=convert_mnemo_num(map, inst.op1);
    int temp=rs;
    execute_next_instruction();
    return;
}*/

void LUI(instruction inst, map_reg * map){
    long immediate=convert_long(inst.op2)<<16;
    int rt=convert_mnemo_num(map, inst.op1);
    modif_reg_num(rt, map, immediate);
    return;
}

void MFHI(instruction inst, map_reg * map){
    int rd=convert_mnemo_num(map, inst.op1);
    long int result=(map[33]->valeur);
    modif_reg_num(rd, map, result);
    return;
}

void MFLO(instruction inst, map_reg * map){
    int rd=convert_mnemo_num(map, inst.op1);
    long int result=(map[34]->valeur);
    modif_reg_num(rd, map, result);
    return;
}

void MULT(instruction inst, map_reg * map){
    int numrs=convert_mnemo_num(map, inst.op1);
    int numrd=convert_mnemo_num(map, inst.op2);
    long int rs=(map[numrs]->valeur);
    long int rd=(map[numrd]->valeur);
    long long int prod=rs*rd;
    long int LO=prod;
    long int HI= prod >> 32 ;
    modif_reg_num(33, map, LO);
    modif_reg_num(34, map, HI);
    return;
}

void NOP(instruction inst, map_reg * map) {
    // Il ne se passe rien, on retourne directement
    return;
}

void OR(instruction inst, map_reg * map){
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op3);
    long int result= (map[rs]->valeur) || (map[rt]->valeur);
    modif_reg_num(rd, map, result);
    return;
}

void ORI(instruction inst, map_reg * map){
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    long int immediate=convert_long(inst.op3);
    long int result= immediate || (map[rs]->valeur);
    modif_reg_num(rd, map, result);
    return;    
}

void SEB(instruction inst, map_reg * map){
    int rd=convert_mnemo_num(map, inst.op1);
    int rt=convert_mnemo_num(map, inst.op2);
    long int masque=0x0000ff;
    long int result= (map[rt]->valeur)&masque;
    int a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        modif_reg_num(rd, map, result);
        return;
    }
}

void SLL(instruction inst, map_reg * map){
    int sa=convert_long(inst.op3);
    int rd=convert_mnemo_num(map, inst.op1);
    int rt=convert_mnemo_num(map, inst.op2);
    long int temp = (map[rt]->valeur) << sa;
    int a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{    
    modif_reg_num(rd, map, temp);
    }
    return;
}

void SLT(instruction inst, map_reg * map){
    int numrs=convert_mnemo_num(map, inst.op2);
    int numrt=convert_mnemo_num(map, inst.op3);
    long int rs=(map[numrs]->valeur);
    long int rt=(map[numrt]->valeur);
    int numrd=convert_mnemo_num(map, inst.op1);
    int a=appartenance_gpr(numrd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        if(rs < rt){
            modif_reg_num(numrd, map, 1);
            return;
        }
        else{
            modif_reg_num(numrd, map, 0);
            return;
        }
    }
}

void SLTI(instruction inst, map_reg * map){
    int numrs=convert_mnemo_num(map, inst.op1);
    long int rs =(map[numrs]->valeur);
    int rt=convert_mnemo_num(map, inst.op2);
    long int immediate=convert_long(inst.op3);
    int a=appartenance_gpr(rt, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        if( rs < immediate){
            modif_reg_num(rt, map, 1);
            return;
        }
        else{
            modif_reg_num(rt, map, 0);
            return;
        }
    }
}

void SLTIU(instruction inst, map_reg * map){
    int numrs=convert_mnemo_num(map, inst.op1);
    unsigned long int rs=(map[numrs]->valeur);
    int rt=convert_mnemo_num(map, inst.op2);
    unsigned long int immediate=convert_long(inst.op3);
    int a=appartenance_gpr(rt, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        if(rs < immediate){
            modif_reg_num(rt, map, 1);
            return;
        }
        else{
            modif_reg_num(rt, map, 0);
            return;
        }
    }
}

void SLTU(instruction inst, map_reg * map){
    int numrs=convert_mnemo_num(map, inst.op1);
    unsigned long int rs=(map[numrs]->valeur);
    int numrt=convert_mnemo_num(map, inst.op2);
    unsigned long int rt=(map[numrt]->valeur);
    int rd=convert_mnemo_num(map, inst.op1);
    int a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        if(rs < rt){
            modif_reg_num(rd, map, 1);
            return;
        }
        else{
            modif_reg_num(rd, map, 0);
            return;
        }
    }
}

void SRA(instruction inst, map_reg * map){
    int sa=convert_long(inst.op3);
    int rd=convert_mnemo_num(map, inst.op1);
    int rt=convert_mnemo_num(map, inst.op2);
    long int temp = convert_long((map[rt]->valeur)) << sa;
    modif_reg_num(rd, map, temp);
    return; 
}

void SRL(instruction inst, map_reg * map){
    int sa=convert_long(inst.op3);
    int rd=convert_mnemo_num(map, inst.op1);
    int rt=convert_mnemo_num(map, inst.op2);
    long int temp = (map[rt]->valeur) >> sa;
    int a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{    
    modif_reg_num(rd, map, temp);
    }
    return;    
}

void SUB (instruction inst, map_reg * map){
    long temp;
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op3);
    int a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        temp=(map[rs]->valeur)-(map[rt]->valeur);
        if( ((map[rs]->valeur)<0) & ((map[rt]->valeur)>0) & (temp>0) ) {
            WARNING_MSG("IntegerOverflow");
            return;
        }
        else if ( ((map[rs]->valeur)>0) & ((map[rt]->valeur)<0) & (temp<0) ) {
            WARNING_MSG("IntegerOverflow");
            return;
        }
        else{
            modif_reg_num(rd, map, temp);
            return;
        }
    }
    return;
}

void SUBU (instruction inst, map_reg * map){
    long temp;
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op3);
    int a;
    a=appartenance_gpr(rd, map);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR");
        return;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas");
        return;
    }
    else{
        temp=(map[rs]->valeur)-(map[rt]->valeur);
        modif_reg_num(rd, map, temp);     
        return;   
    }
}

void XOR(instruction inst, map_reg * map){
    int rd=convert_mnemo_num(map, inst.op1);
    int rs=convert_mnemo_num(map, inst.op2);
    int rt=convert_mnemo_num(map, inst.op3);
    long int result= (map[rs]->valeur) ^ (map[rt]->valeur);
    modif_reg_num(rd, map, result);
    return;
}

int main(){
	map_reg* map=creer_map_reg();
	modif_reg_num (8, map, 9);
	modif_reg_num (9, map, 8);
	modif_reg_num (10, map, 7);
    
	instruction inst;
    inst.def=NULL;
    inst.op1=calloc(3, sizeof(*inst.op1));
    inst.op1="$t0";
    inst.op2=calloc(3, sizeof(*inst.op2));
    inst.op2="$t1";
    inst.op3=calloc(3, sizeof(*inst.op3));
    inst.op3="$t2";
    inst.op4=NULL;
    printf("On a : rd=registre 8 <- 9; rs=registre 9 <- 8, rt=regisre 10 <-7 \n");
	ADD(inst, map);
	printf("ADD rd, rs, rt = %ld -> On attend 15\n",map[8]->valeur);
	ADDU(inst, map);
	printf("ADDU rd, rs, rt = %ld -> On attend 15\n",map[8]->valeur);
	SUB(inst, map);
	printf("SUB rd, rs, rt = %ld -> On attend 1 \n",map[8]->valeur);
	SUBU(inst, map);
	printf("SUBU rd, rs, rt : %ld -> On attend 1\n",map[8]->valeur);
    
	modif_reg_num (8, map, 11);
	modif_reg_num (9, map, 5);
	modif_reg_num (10, map, 7);
    printf("On a : rd=registre 8 <-11; rs=registre 9 <- 5, rt=regisre 10 <-7\n");
    
	MULT(inst, map);
	printf("MULT rd, rs: HI=%ld (attendu 55); LO=%ld (attendu 0) \n",map[33]->valeur, map[34]->valeur);
	DIV(inst, map);
	printf("DIV rd, rs : HI=%ld (attendu 2); LO=%ld (attendu1) \n", map[33]->valeur, map[34]->valeur);
    
    
	modif_reg_num (8, map, 9);
	modif_reg_num (9, map, 8);
	modif_reg_num (10, map, 7);
    printf("On a : rd=registre 8 <-9; rs=registre 9 <- 8, rt=regisre 10 <-9\n");
    
	AND(inst, map);
	printf("AND rd, rs, rt  = %ld (attendu 8 <-> 1000=1001&1000) \n",map[8]->valeur);
	OR(inst, map);
	printf(" OR rd, rs, rt = %ld (attendu 9 <-> 1001=1001||1000)\n",map[8]->valeur);
	XOR(inst, map);
	printf("XOR rd, rs, rt = %ld (attendu 1 <-> 0001=1001 XOR 1000)\n",map[8]->valeur);
    
	SLT(inst, map);
	printf("SLT rd, rs, rt -> rd=%ld (attendu 0 car rs>rd) \n",map[8]->valeur);
	SLTU(inst, map);
	printf("SLTU rd, rs, rt -> rd=%ld (attendu 0 car rs>rd) \n",map[8]->valeur);
	MFHI(inst, map);
	printf("MFHI : %ld (attendu 2 de la division)\n",map[33]->valeur);
	MFLO(inst, map);
	printf("MFLO : %ld (attendu 1 de la division) \n",map[34]->valeur);
    
    
    
	instruction inst1;
    inst1.def=NULL;
    inst1.op1=calloc(3, sizeof(*inst.op1));
    inst1.op1="$t0";
    inst1.op2=calloc(3, sizeof(*inst.op2));
    inst1.op2="$t1";
    inst1.op3=calloc(3, sizeof(*inst.op3));
    inst1.op3="9";
    inst1.op4=NULL;
    modif_reg_num (8, map, 9);
    modif_reg_num (9, map, 8);
    printf("On a : rd=registre 8 <- 9; rs=registre 9 <- 8, immediate=9\n");
	ADDI(inst1, map);
	printf("ADDI rd, rs, immediate = %ld (attendu 17) \n", map[8]->valeur);
	ADDIU(inst1, map);
	printf("ADDIU rd, rs, immediate = %ld (attendu 17) \n", map[8]->valeur);
	ANDI(inst1, map);
	printf("ANDI rd, rs, immediate = %ld (attendu 8 <-> 1000=1001&1000)\n", map[8]->valeur);
	ORI(inst1, map);
	printf("ORI rd, rs, immediate = %ld (attendu 9 <-> 1001=1001||1000)\n", map[8]->valeur);
	SLTI(inst1, map);
	printf("SLTI rt, rs, immediate = %ld (attendu 1) \n", map[8]->valeur);
	SLTIU(inst1, map);
	printf("SLTIU rt, rs, immediate = %ld (attendu 1) \n", map[8]->valeur);
    
    
    
	instruction inst2;
    inst2.def=NULL;
    inst2.op1=calloc(3, sizeof(*inst.op1));
    inst2.op1="$t00";
    inst2.op2=calloc(3, sizeof(*inst.op2));
    inst2.op2="$t10";
    inst2.op3=calloc(3, sizeof(*inst.op3));
    inst2.op3="12";
    inst2.op4=NULL;
    modif_reg_num (8, map, 8);
    modif_reg_num (9, map, 8);
    printf("On a : rd=registre 8 <- 8; rs=registre 9 <- 8, offset=12 et PC= %ld\n", map[32]->valeur);
	BNE(inst2, map);
	printf("BNE rs, rt, offset -> PC=%ld (attendu 1 car PC=0+1 dû à la différence entre rs et rt) \n", map[32]->valeur);
	BEQ(inst2, map);
	printf("BEQ rs, rt, offset -> PC=%ld (attendu PC=1+1+offset avec offset=48 <-> 1100<<2 car 1100<->12 ) \n", map[32]->valeur);
    
	modif_reg_num (32, map, 0);
	printf("PC = %ld \n", map[32]->valeur);
	modif_reg_num (8, map, 9);
	modif_reg_num (9, map, 8);
	BEQ(inst2, map);
	printf("BEQ rs, rt, offset -> PC=%ld (attendu PC=0+1 dû à l'égalité entre rs et rt\n", map[32]->valeur);
	BNE(inst2, map);
	printf("BNE rs, rt, offset -> PC= %ld (attendu PC=1+1+offset avec offset=48 <-> 1100<<2 car 1100<->12 )\n", map[32]->valeur);
}