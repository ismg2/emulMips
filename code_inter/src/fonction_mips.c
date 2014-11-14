#include "fonction_mips.h"
/*
int addi(map_reg * mrg,mem memoire,union_RIJ union_struct)
{
	uint32_t registre_rs;
	uint32_t registre_rt;

	registre_rs = renvoi_reg_num(mrg,union_struct.i.rs	DEBUG_MSG("rs = %u",registre_rs);
	registre_rt = registre_rs + union_struct.i.immediate;
	DEBUG_MSG("immediate : %d",union_struct.i.immediate);
	DEBUG_MSG("rt : %u",registre_rt);
	modif_reg_num(union_struct.i.rt,mrg,registre_rt);
	return 1;
}
*/
int appartenance_gpr(int rd, map_reg * map) {
    unsigned int a;
    if(rd>34 || rd<0) {
        a=1;
        return a;
    }
    //else if(rd>23 || rd<8) {
     //   a=2;
      //  return a;
    //}
    else {
        a=0;
        return 0;
    }
}

// Fonction ADD
int ADD (map_reg * mrg,mem memoire,union_RIJ  union_struct){
    long temp;
    unsigned int rd=union_struct.r.rd;//convert_mnemo_num(map, inst.op1);
    unsigned int rs=union_struct.r.rs;
    unsigned int rt=union_struct.r.rt;
    DEBUG_MSG("ON rentre dans ADD");
    int a;
    a=appartenance_gpr(rd, mrg);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR"); // Test : ça marche ?
        return 0;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas"); // Test : ça marche ?
        return 0;
    }
    else{
        temp= mrg[rs]->valeur+ mrg[rt]->valeur;
        // Gestion des IntegerOverflow
        if((temp&MOF) == MOF ) {
            WARNING_MSG("IntegerOverflow");
            return 0;
        }
        else if ( mrg[rs]->valeur>0 &&  mrg[rt]->valeur>0 && temp<0 ) {
            WARNING_MSG("IntegerOverflow");
            return 0;
        }
        else{
            modif_reg_num(rd, mrg, temp);
            return 1;
        }
    }
    return 0;
}

// Fonction ADDI rd, rs, rt ==>  rd <- rs+registres
int ADDI (map_reg * mrg,mem memoire,union_RIJ  union_struct){
    long temp;
    unsigned int rt=union_struct.i.rt;
    unsigned int rs=union_struct.i.rs;
    int immediate=union_struct.i.immediate;
    DEBUG_MSG("ON rentre dans ADDI");
    int a;
    a=appartenance_gpr(rt, mrg);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR"); // Test : ça marche ?
        return 0;                                                                                  
    }                                                                                                                                                           
    else if(a==2) {                                                                                                                         
        WARNING_MSG("Votre registre de destination n'existe pas"); // Test : ça marche ?
        return 0;
    }                                                                                                                           
    else{                                                                                                       
        temp= mrg[rs]->valeur + immediate;
        if((temp&MOF) == MOF ) {
            WARNING_MSG("IntegerOverflow");
            return 0;
        }
        else{
        modif_reg_num(rt, mrg, temp);
        return 1;
        }                                                                
    }
    return 0;                                                                                                          
}

// Fonction ADDIU rd, rs, rt ==>  rd <- rs+registres
int ADDIU (map_reg * mrg,mem memoire,union_RIJ  union_struct){
    long temp;
    unsigned int rt=union_struct.i.rt;
    unsigned int rs=union_struct.i.rs;
    int immediate=union_struct.i.immediate;
    DEBUG_MSG("ON rentre dans ADDIU");
    int a;
    a=appartenance_gpr(rt, mrg);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR"); // Test : ça marche ?
        return 0;
    }                                                                                                                                                           
    else if(a==2) {                                                                                                                         
        WARNING_MSG("Votre registre de destination n'existe pas"); // Test : ça marche ?
        return 0;
    }                                                                                                                           
    else{                                                                                                       
        temp= mrg[rs]->valeur + immediate;                                                                
        modif_reg_num(rt, mrg, temp);
        return 1;
    }                                                                                                                
}

// Fonction ADDU rd, rs, rt ==>  rd <- rs+rt
int ADDU (map_reg * mrg,mem memoire,union_RIJ  union_struct){
    long temp;
    unsigned int rd=union_struct.r.rd;
    unsigned int rs=union_struct.r.rs;
    unsigned int rt=union_struct.r.rt;
    DEBUG_MSG("ON rentre dans ADDU");
    int a;
    a=appartenance_gpr(rd, mrg);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR"); // Test : ça marche ?
        return 0;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas"); // Test : ça marche ?
        return 0;
    }
    else{
        // Test : les registres sources appartiennent à notre mrg_reg * ?
        temp= mrg[rs]->valeur+  mrg[rt]->valeur;
        modif_reg_num(rd, mrg, temp);    
        return 1;   
    }
}

// Fonction AND
int AND (map_reg * mrg,mem memoire,union_RIJ  union_struct) {
    long temp;
    unsigned int rd=union_struct.r.rd;
    unsigned int rs=union_struct.r.rs;
    unsigned int rt=union_struct.r.rs;
    DEBUG_MSG("ON rentre dans AND");
    int a;
    a=appartenance_gpr(rd, mrg);
    if(a==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR"); // Test : ça marche ?
        return 0;
    }
    else if(a==2) {
        WARNING_MSG("Votre registre de destination n'existe pas"); // Test : ça marche ?
        return 0;
    }
    else{
        temp= mrg[rs]->valeur&mrg[rt]->valeur;
        modif_reg_num(rd, mrg, temp);
        return 1;
    }
}

int ANDI (map_reg * mrg,mem memoire,union_RIJ  union_struct) {
    long temp;
    int immediate=union_struct.i.immediate;
    unsigned int rs=union_struct.i.rs;
    unsigned int rt=union_struct.i.rt;
    DEBUG_MSG("ON rentre dans ANDI");
    int a;int b;
    a=appartenance_gpr(rs, mrg);
    b = appartenance_gpr(rt, mrg);
    if(a==1 || b==1) {
        WARNING_MSG("Votre registre de destination n'appartient pas au GPR"); // Test : ça marche ?
        return 0;
    }
    else if(a==2 || b==2) {
        WARNING_MSG("Votre registre de destination n'existe pas"); // Test : ça marche ?
        return 0;
    }
    else{
        temp= mrg[rs]->valeur&immediate;
        modif_reg_num(rt, mrg, temp);
        return 1;
    }
}
// AR
int BEQ(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    unsigned int rs=mrg[union_struct.i.rs]->valeur;
    unsigned int rt=mrg[union_struct.i.rt]->valeur;
    int offset=union_struct.i.immediate;
    DEBUG_MSG("ON rentre dans BEQ");
    int result;
    if(rs==rt){
        result=mrg[32]->valeur+offset;
        modif_reg_num(32, mrg, result);
        return 1;
    }
    else{
        //result=mrg[32]->valeur+1;
        //modif_reg_num(32, mrg, result);
        return 0;
    }
}

int BGEZ(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    int rs=mrg[union_struct.i.rs]->valeur;
    int offset=union_struct.i.immediate;
    int result;
    DEBUG_MSG("ON rentre dans BGEZ");
    if(rs>=0){
        result=mrg[32]->valeur+offset;
        modif_reg_num(32, mrg, result);
        return 1;
    }
    else{
        //result=(mrg+32)->valeur+1;
        //modif_reg_num(32, mrg, result);
        return 0;
    }
}

int BGTZ(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    unsigned int rs=union_struct.i.rs;
    int offset=union_struct.i.immediate;
    DEBUG_MSG("ON rentre dans BGTZ");
    int result;
    if(rs>0){
        result=mrg[32]->valeur+offset;
        modif_reg_num(32, mrg, result);
        return 1;
    }
    else{
        //result=(mrg+32)->valeur+1;
        //modif_reg_num(32, mrg, result);
        return 0;
    }
}

int BLEZ(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    unsigned int rs=mrg[union_struct.i.rs]->valeur;
    int offset=union_struct.i.immediate;
    DEBUG_MSG("ON rentre dans BLEZ");
    int result;
    if(rs<=0){
        result=mrg[32]->valeur+offset;
        modif_reg_num(32, mrg, result);
        return 1;
    }
    else{
        //result=mrg[32]->valeur+1;
        //modif_reg_num(32, mrg, result);
        return 1;
    }
}

int BLTZ(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    int rs=mrg[union_struct.i.rs]->valeur;
    int offset=union_struct.i.immediate;
    DEBUG_MSG("ON rentre dans BLTZ");
    int result;
    if(rs<0){
        result=mrg[32]->valeur+offset;
        modif_reg_num(32, mrg, result);
        return 1;
    }
    else{
        //result=(mrg+32)->valeur+1;
        //modif_reg_num(32, mrg, result);
        return 1;
    }
}

int BNE(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    unsigned int rs=mrg[union_struct.i.rs]->valeur;
    unsigned int rt=mrg[union_struct.i.rt]->valeur;
    DEBUG_MSG("ON rentre dans BNE");
    DEBUG_MSG("RS : %02x -- RT = %02x",rs,rt);
    int offset=union_struct.i.immediate;
    int result;
    if(rs==rt)
    {
        return 1;
    }
    else if(rs!=rt){
        result=mrg[32]->valeur+offset*4;
        modif_reg_num(32, mrg, result);
        return 1;
    }
    else return 0;
}

int MFHI(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    int rd=union_struct.r.rd;
    unsigned int result=mrg[33]->valeur;
    modif_reg_num(rd, mrg, result);
    DEBUG_MSG("ON rentre dans MFHI");
    return 1;
}

int MFLO(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    unsigned int rd=union_struct.r.rd;
    unsigned int result=mrg[34]->valeur;
    modif_reg_num(rd, mrg, result);
    DEBUG_MSG("ON rentre dans MFLO");
    return 1;
}

int NOP(map_reg * mrg,mem memoire,union_RIJ  union_struct) {

	DEBUG_MSG("ON rentre dans NOP");

    return 1;
}

int BREAK(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans BREAK");
	return 2;
}
int DIV(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans DIV");
    unsigned int rs = mrg[union_struct.r.rs]->valeur;
    unsigned int rt = mrg[union_struct.r.rt]->valeur;
    int q,r;
    q = rs/rt;
    modif_reg_num(34,mrg,q);
    r = rs % rt;
    modif_reg_num(33,mrg,r);
    return 1;
}
int j(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans j");
	return 1;
}
int JAL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans JAL");
	return 1;

}
int JALR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans JALR");

	return 1;
}
int JR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans JR");
	return 1;
}
int LB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LB");
	return 1;
}

int LBU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LBU");
	return 1;
}

int LUI(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LUI");
	return 1;
}
int LW(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LW");
	return 1;
}
int MULT(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans MULT");
	return 1;
}
int OR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans OR");
	return 1;
}
int ORI(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans ORI");
	return 1;
}
int SB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SB");
	return 1;
}
int SEB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SEB");
	return 1;
}
int SLL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLL");
	return 1;
}
int SLT(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLT");
	return 1;
}
int SLTI(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLTI");
	return 1;
}
int SLTIU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLTIU");
	return 1;
}
int SLTU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLTU");
	return 1;
}
int SRA(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SRA");
	return 1;
}
int SRL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SRL");
	return 1;
}
int SUB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SUB");
	return 1;
}
int SUBU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SUBU");
	return 1;
}
int SW(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SW");
	return 1;
}
int SYSCALL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SYSCALL");
	return 1;
}
int XOR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans XOR");
	return 1;
}