.set noreorder   

_start:
.global _start

addi $t1,$zero,8
add $t2,$zero,$t1
SLL $t1,$t1,2
JAL 0x5024      # appel explicite Ã  l'adresse de la procedure  
NOP
BEQ $t1,$t2,0x38  # branchement Ã  OK si les deux valeurs sont Ã©gales
NOP
J 0x505C 						# sinon saut Ã  KO
NOP


procedure:
 ADDI $sp,$sp,-4
 SW $31,0($sp)   # on stocke l'adresse de retour
 ADDI $sp,$sp,-4 # on decremente le pointeur de pile
 SW $t1,0($sp)   # on stocke les registres sur lesquels la procedure agit (ici $t1 seulement)

 SRL $t2,$t1,2

 LW $t1,0($sp)   # on recupere les registres sur lesquels la procedure agit (ici $t1 seulement)
 ADDI $sp,$sp,4
 LW $31,0($sp)   # on recupere l'adresse de retour
 ADDI $sp,$sp,4

 JR $31
nop

OK:
ADDI $v0,$zero,8  # appel explicite Ã  scan
ADDI $a0,$zero,0x6008
ADDI $a1,$zero,8   
syscall #lit la chaine
KO:
ADDI $v0,$zero,4
ADDI $a0,$zero,0x6008 #affiche la chaine
syscall

.data 
chaine: .asciiz "Youpi"