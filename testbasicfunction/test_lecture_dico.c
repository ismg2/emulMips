#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOM 64


typedef struct {
  uint32_t signature;
  uint32_t masque;
  char nom[MAX_NOM];
  char type;
  char * op_mapping[MAX_NOM];
  int nmbr_oper;
} *definition;


int lecture_cmd(char * file_name)
{
FILE * fp;

fp=fopen(file_name,'r');
char * ligne;
definition def;
def = calloc(24,sizeof(*def));





if(fp==NULL) { printf("\nImpoosible d'ouvrir le fichier test ");}

else {


  while(fgets(ligne,128,fp)!=NULL)
  { int j=0;

      char * token=strtok(ligne,"");
      sscanf(token,"%s",(def[j].nom));
      printf("\nNOM : %s\n");

      token=strtok(NULL,"");
      sscanf(token,"%c",(def[j].type));
      printf("\n TYPE : %c\n",def[j].type);

      token=strtok(NULL,"");
      sscanf(token,"%x",&(def[j].signature));
      printf("\n SIGNATURE : %08x\n",def[j].signature);


      token=strtok(NULL,"");
      sscanf(token,"%x",&(def[j].masque));
      printf("\n MASQUE: %08x\n",def[j].masque);


      token=strtok(NULL,"");
      sscanf(token,"%d",&(def[j].nmbr_oper));
      printf("\n NBR OPERANDE : %d\n",def[j].nmbr_oper);
      
      for (int i = 0; i < def[j].nmbr_oper ; i++)
          { token=strtok(NULL,"");
          char *temp;
          sscanf(token,"%s",(def[j].op_mapping[i]));
          def->op_mapping[i]=strdup(temp);
          printf("\n OPERANDE : %s\n",def[j].op_mapping[i]);
          }
   }
}

return 1;}



int main()

{
  char * fichier_nom="dico_def.txt";
  int verif=lecture_cmd(fichier_nom);

return 0;}








































