#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define MAX_NOM 64


typedef struct {
  uint32_t signature;
  uint32_t masque;
  char nom[MAX_NOM];
  char  type;
  char * op_mapping[MAX_NOM];
  int nmbr_oper;
} *definition;

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

//On lit toutes les commandes du dictionnaire et on affiche toutes les caracteristiques

int main() { 

  char fichier_nom[64]="dico_definitif.txt";
  printf(" %s \n",fichier_nom);
  lecture_cmd(fichier_nom);


}








































