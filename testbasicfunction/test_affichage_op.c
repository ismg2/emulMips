#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_NOM 64

typedef struct {
  uint32_t signature;
  uint32_t masque;
  char nom[MAX_NOM];
  char  type;
  char * op_mapping[MAX_NOM];
  int nmbr_oper;
} *definition;


typedef struct {
	unsigned int function : 6;
	unsigned int sa : 5;
	unsigned int rd : 5;
	unsigned int rt : 5;
	unsigned int rs : 5;
	unsigned int opcode : 6;

}R;

typedef struct {
	int immediate : 16; //
	unsigned int rt : 5;
	unsigned int rs : 5;
	unsigned int opcode : 6;

}I;


typedef struct {
	unsigned int target : 26;
	unsigned int opcode : 6;
}J;



/**
 * Lecture du fichier texte regroupant toutes les commandes et affiche le tableau memmoire allooué pour
 * @param file_name : nom du dictionnaire de toutes les commandes
 */
void lecture_cmd(char * file_name)
{
    
FILE * fp;
fp=fopen(file_name,"r");
char * ligne = NULL;
definition def = NULL;
definition temp = NULL;
def = calloc(1028,sizeof(*def));
temp = calloc(2,sizeof(*def));
ligne = calloc (2054,sizeof(*ligne));
 
if(fp==NULL) { printf("\nImpoosible d'ouvrir le fichier test ");}
else {int j=0;

  while(fgets(ligne,2054,fp)!=NULL)
  { 
    printf("---------------------------------------------------\n");
    printf("---------------------------------------------------\n");
    //printf("\n LIGNE : %s \n",ligne);
      char * token=strtok(ligne,"   ");
      sscanf(token,"%s",(def[j].nom));
      printf("\n NOM : %s",(def[j].nom));

      token=strtok(NULL,"   ");
      sscanf(token,"%s",&(def[j].type));
      printf("\n TYPE : %c ",def[j].type);

      token=strtok(NULL,"   ");
      sscanf(token,"%x",&(temp->signature));
      def[j].signature = (temp->signature);
      printf("\n SIGNATURE : %08x ",def[j].signature);


      token=strtok(NULL,"   ");
      sscanf(token,"%x",&(temp->masque));
      def[j].masque = temp->masque;
      printf("\n MASQUE: %08x",def[j].masque);


      token=strtok(NULL,"   ");
      sscanf(token,"%d",&(def[j].nmbr_oper));
      printf("\n NBR OPERANDE : %d\n",def[j].nmbr_oper);
      if(def[j].nmbr_oper!=0)
      {
        for (int i = 0; i < def[j].nmbr_oper ; i++)
          { token=strtok(NULL,"   ");
            char * tempo = calloc(2,sizeof(*tempo));
            sscanf(token,"%s",tempo);
            def[j].op_mapping[i]=strdup(tempo);
            printf("\t OPERANDE numero %d : %s\n",i+1,def[j].op_mapping[i]);
          }
      }
      printf("\n\n\n");
      j++;
    }
}

//return 1;
}


//Premiere essai pour afficher les differentes opérandes d'un mot pris du fichier ELF
//On affiche les numero des registres pour le moment ! Pas de mnemonique !




int main(void)
{
I b;
    uint32_t a=0x2009000c;
    printf("On affiche d'abord le mot a : %08x \n",a);
    uint32_t masque_rs =0x3E00000;
    uint32_t masque_rt = 0x1F0000;
    uint32_t masque_rd = 0xF800;
    uint32_t masque_sa = 0x7C0;
    int masque_immediate =0xffff ; //
     b.rs = (a & masque_rs) >> 21;
     b.rt = (a & masque_rt) >> 16;
     b.rd = (a & masque_rd) >> 11;
     b.sa = (a & masque_sa) >> 6 ;
     b.immediate =(int) (a & masque_immediate); //
     printf("On recupere immediate : %08x -- %d --- %d \n",b.immediate,b.immediate,temp_signed);
    printf (" rs : %u \t rt : %u \t immediate : %d \n",b.rs,b.rt,b.immediate);


//    bin_print_int(a);
//    unsigned int a_B = bin_return_int(a);
//    printf("AVEC LA NOUVELLE FONCTION : %u \n",a_B);
    return 0;
}



/*
int main() { 

R b;

b.function =000000; 
b.sa =00011; 
b.rd =00100;
b.rt =00010; 
b.rs =00000;
b.opcode =100000;




}
*/

