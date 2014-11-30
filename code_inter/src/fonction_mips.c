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
/*
uint32_t sign_extend_16(uint16_t immediate)
{
    if
}

uint32_t sign_extend_8(uint16_t immediate)
*/


// Fonction ADD
int ADD (map_reg * mrg,mem memoire,union_RIJ  union_struct){
    long temp;
    uint32_t rd=union_struct.r.rd;//convert_mnemo_num(map, inst.op1);
    uint32_t rs=union_struct.r.rs;
    uint32_t rt=union_struct.r.rt;
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
    DEBUG_MSG("ON a rs = %08x et rt = %08x",rs,rt);
    int result;
    if(rs==rt){
        result=mrg[32]->valeur+offset*4;
        modif_reg_num(32, mrg, result);
        return 1;
    }
    else{
        //result=mrg[32]->valeur+1;
        //modif_reg_num(32, mrg, result);
        return 1;
    }
}

int BGEZ(map_reg * mrg,mem memoire,union_RIJ  union_struct){
    int rs=mrg[union_struct.i.rs]->valeur;
    int offset=union_struct.i.immediate;
    int result;
    DEBUG_MSG("ON rentre dans BGEZ");
    if(rs>=0){
        result=mrg[32]->valeur+offset*4;
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
        result=mrg[32]->valeur+offset*4;
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
        result=mrg[32]->valeur+offset*4;
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
        result=mrg[32]->valeur+offset*4;
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
	return 7;
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

uint32_t masque_pc = 0xF0000000;
uint32_t target = union_struct.j.target;
uint32_t PC = renvoi_reg_num(mrg,32);
    target = target << 2;
    PC = (PC & masque_pc) | target ;
    modif_reg_num(32,mrg,PC); 
	return 1;
}
int JAL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans JAL");

uint32_t masque_pc = 0xF0000000;
uint32_t target = union_struct.j.target;
uint32_t PC = renvoi_reg_num(mrg,32);
    modif_reg_num(31,mrg,PC+4);
    target = target << 2;
    PC = (PC & masque_pc) | target ; 
    modif_reg_num(32,mrg,PC); 
    return 1;	
}
int JALR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans JALR");
    uint32_t rs = mrg[union_struct.r.rs]->valeur;
    uint32_t rd;
    uint32_t PC;
    if(union_struct.r.rd != 0) rd = mrg[union_struct.r.rd]->valeur;
    else rd = 0;
    PC = renvoi_reg_num(mrg,32);
    modif_reg_num(32,mrg,rs);
    if(union_struct.r.rd != 0) modif_reg_num(union_struct.r.rd,mrg,PC+8);
    else modif_reg_num(31,mrg,PC+8);
	return 1;
}
int JR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	uint32_t rs = mrg[union_struct.r.rs]->valeur;
    modif_reg_num(32,mrg,rs);
    DEBUG_MSG("ON rentre dans JR");
	return 1;
}
int LB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LB");
    uint32_t base = mrg[union_struct.i.rs]->valeur ;
    //uint32_t rt = mrg[union_struct.i.rt];
    int offset = union_struct.i.immediate;
    uint32_t word;
    uint32_t vaddr = base + (uint32_t) offset;
    uint8_t byte = renvoi_byte(memoire,vaddr,mrg);
    if((masque_8b & byte) == masque_8b)
    {
        word = 0xFFFFFF00 | (uint32_t) byte; 
    }
    else word = (uint32_t) byte;
	modif_reg_num(union_struct.i.rt,mrg,word);
    return 1;
}

int LBU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LBU");
    uint32_t base = mrg[union_struct.i.rs]->valeur ;
    //uint32_t rt = mrg[union_struct.i.rt];
    int offset = union_struct.i.immediate;
    uint32_t vaddr = base + (uint32_t) offset;
    uint8_t byte = renvoi_byte(memoire,vaddr,mrg);
    uint32_t word = (uint32_t) byte;
    modif_reg_num(union_struct.i.rt,mrg,word);
	return 1;
}

int LUI(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LUI");
    uint32_t immediate = union_struct.i.immediate << 16;
    modif_reg_num(union_struct.i.rt,mrg,immediate);
	return 1;
}
int LW(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans LW");
	uint32_t offset = union_struct.i.immediate;
    uint32_t vaddr = offset + mrg[union_struct.i.rs]->valeur;
    uint32_t word = renvoi_mot(memoire,vaddr,mrg);
    modif_reg_num(union_struct.i.rt,mrg,word);
    return 1;
}
int MULT(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans MULT");
    uint32_t rs = mrg[union_struct.r.rs]->valeur;
    uint32_t rt = mrg[union_struct.r.rt]->valeur;
    uint64_t prod = rs * rt;
    uint32_t prod0_31 = prod & 0xFFFFFFFF;
    uint32_t prod32_63 = ( prod >> 32 ) & 0xFFFFFFFF;
    modif_reg_num(34,mrg,prod0_31);
    modif_reg_num(33,mrg,prod32_63);
	return 1;
}
int OR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans OR");
    uint32_t rs = mrg[union_struct.r.rs]->valeur;
    uint32_t rt = mrg[union_struct.r.rt]->valeur;
    uint32_t rd;
    rd = rs | rt;
    modif_reg_num(union_struct.r.rd,mrg,rd);
	return 1;
}
int ORI(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans ORI");
    uint32_t rs = mrg[union_struct.i.rs]->valeur;
    uint32_t immediate = mrg[union_struct.i.immediate]->valeur;
    uint32_t rt;
    rt = rs | immediate;
    modif_reg_num(union_struct.i.rt,mrg,rt);
	return 1;
}

int SB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SB");
    uint32_t vaddr = mrg[union_struct.i.rs]->valeur + union_struct.i.immediate;
    uint32_t rt = mrg[union_struct.i.rt]->valeur;
    uint8_t byte_1 = rt & byte1;
    int res;

    res = set_byte(memoire,vaddr,byte_1,mrg);
    if(res == 0) return 0;

    else return 1;
}
int SEB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SEB");
    uint8_t rt_8 = mrg[union_struct.r.rt]->valeur;
    uint32_t rt = 0;
    if( (rt&masque_8b) == masque_8b) rt = rt_8 | 0xFFFFFF00 ;
    else rt = (uint32_t) rt_8;
    modif_reg_num(union_struct.r.rd,mrg,rt);
	return 1;
}
int SLL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLL");
    int s = union_struct.r.sa;
    uint32_t temp = mrg[union_struct.r.rt]->valeur << s;
    modif_reg_num(union_struct.r.rd,mrg,temp);
	return 1;
}
int SLT(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLT");

    if( mrg[union_struct.r.rs]->valeur < mrg[union_struct.r.rt]->valeur )
        modif_reg_num(union_struct.r.rd,mrg,1);
    else modif_reg_num(union_struct.r.rd,mrg,0);
	return 1;
}
int SLTI(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLTI");
    uint16_t imm = mrg[union_struct.i.immediate]->valeur;
    uint32_t imm_32;
    if((imm&masque_16b)==masque_16b) imm_32 = imm | 0xFFFF0000;
    else imm_32 = (uint32_t) imm;
        if( mrg[union_struct.i.rs]->valeur < imm_32 )
        modif_reg_num(union_struct.i.rt,mrg,1);
    else modif_reg_num(union_struct.i.rt,mrg,0);
	return 1;
}
int SLTIU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLTIU");
    uint16_t imm = mrg[union_struct.i.immediate]->valeur;
    uint32_t imm_32;
    if((imm&masque_16b)==masque_16b) imm_32 = imm | 0xFFFF0000;
    else imm_32 = (uint32_t) imm;
        if( mrg[union_struct.i.rs]->valeur < imm_32 )
        modif_reg_num(union_struct.i.rt,mrg,1);
    else modif_reg_num(union_struct.i.rt,mrg,0);
	return 1;
}
int SLTU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SLTU");
    uint32_t rs = mrg[union_struct.r.rs]->valeur;
    uint32_t rt = mrg[union_struct.r.rt]->valeur;
        if( rs < rt )
        modif_reg_num(union_struct.r.rd,mrg,1);
    else modif_reg_num(union_struct.r.rd,mrg,0);
	return 1;
}
int SRA(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SRA");
    int s = union_struct.r.sa;
    uint32_t bit_signe = mrg[union_struct.r.rt]->valeur & masque_32b;
    uint32_t temp = bit_signe|( mrg[union_struct.r.rt]->valeur >> s ) ;
    modif_reg_num(union_struct.r.rd,mrg,temp);
	return 1;
}
int SRL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SRL");
    int s = union_struct.r.sa;
    uint32_t temp =  mrg[union_struct.r.rt]->valeur >> s  ;
    modif_reg_num(union_struct.r.rd,mrg,temp);
	return 1;
}
int SUB(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SUB");
    long temp;
    uint32_t rd=union_struct.r.rd;
    uint32_t rs=union_struct.r.rs;
    uint32_t rt=union_struct.r.rt;
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
        temp= mrg[rs]->valeur - mrg[rt]->valeur;
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
int SUBU(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SUBU");
    long temp;
    uint32_t rd=union_struct.r.rd;
    uint32_t rs=union_struct.r.rs;
    uint32_t rt=union_struct.r.rt;
    temp= mrg[rs]->valeur - mrg[rt]->valeur;
    modif_reg_num(rd, mrg, temp);
	return 1;
}

int SW(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans SW");
    uint32_t vaddr = mrg[union_struct.i.rs]->valeur + union_struct.i.immediate;
    uint32_t rt = mrg[union_struct.i.rt]->valeur;
    uint8_t byte_1 = rt & byte1;
    uint8_t byte_2 = (rt & byte2) >> 8;
    uint8_t byte_3 = (rt & byte3) >> 16;
    uint8_t byte_4 = (rt & byte4) >> 24;
    int res;
    // On ecrit toujours dans l'adresse la plus faible puis on decale Donc il faut ecrire les bit de poid faible d'abord puis les translaté
    if(union_struct.i.rs == 29)
    {
        res = set_byte(memoire,vaddr,byte_1,mrg);
        if(res == 0) return 0;
        res = set_byte(memoire,vaddr,byte_2,mrg);
        if(res == 0) return 0;
        res = set_byte(memoire,vaddr,byte_3,mrg);
        if(res == 0) return 0;
        res = set_byte(memoire,vaddr,byte_4,mrg);
        if(res == 0) return 0;
        return 1;
    }
    //ici on ecrit dans le sens big endian cad les bit de poid fort (pex bit4) au adresse les plus basses 
    else 
    {
        res = set_byte(memoire,vaddr,byte_4,mrg);
        if(res == 0) return 0;
        res = set_byte(memoire,vaddr+1,byte_3,mrg);
        if(res == 0) return 0;
        res = set_byte(memoire,vaddr+2,byte_2,mrg);
        if(res == 0) return 0;
        res = set_byte(memoire,vaddr+3,byte_1,mrg);
        if(res == 0) return 0;
        return 1;
    }
    
}
int SYSCALL(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
DEBUG_MSG("ON rentre dans SYSCALL");
uint32_t v0_u = renvoi_reg_num(mrg,2);
uint32_t a0;
uint32_t a0_;
int i;
//int v0 = (int) v0_u;
switch(v0_u)
    {
    case 1 : 
    a0_ = renvoi_reg_num(mrg,4);
    printf("\nOn affiche l'entier contenu dans le registre $a0\n");
    printf(" \n $a0 : 0x%08x \n",a0_);
    break; 

    case 4 : 
    a0 = renvoi_reg_num(mrg,4); // adresse ou se trouve la chaine de caractere
    uint64_t ascii= (uint64_t) renvoi_mot(memoire,a0,mrg);
    uint64_t ascii_z = (uint64_t) renvoi_mot(memoire,a0+4,mrg);
    ascii = (ascii << 32) | ascii_z;  // On renvoit le code asciiz du mot
    FLIP_ENDIANNESS(ascii);
    char * string =  (char *) &ascii;
    printf("\nOn affiche la chaine contenu à l'adresse %08x \n",a0);
    printf("\n STRING : %s \n",string);
    break;

    case 5 : printf("\n Entrez un entier : \n");
    int v0;
    scanf("%d",&v0);
    modif_reg_num(2,mrg,v0);
    break;

    case 8 : printf("Entrez un chaine de caractère");
    uint64_t a0 = renvoi_reg_num(mrg,4);
    uint64_t a1 = renvoi_reg_num(mrg,5);
    char * adresse = (void *) a0;
    adresse = calloc(a1,sizeof(*adresse));
    scanf("%s",adresse);
    break;

    case 10 :
    return 0;
    break;

    default : return 0;
    }
return 1;
}
int XOR(map_reg * mrg,mem memoire,union_RIJ  union_struct)
{
	DEBUG_MSG("ON rentre dans XOR");
    uint32_t rs = mrg[union_struct.r.rs]->valeur;
    uint32_t rt = mrg[union_struct.r.rt]->valeur;
    uint32_t temp = rs^rt;
    modif_reg_num(union_struct.r.rd,mrg,temp); 
	return 1;
}