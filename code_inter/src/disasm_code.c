#include "disasm_code.h"


int lecture_cmd(char * file_name,)
{
FILE * fp;

fp=fopen(file_name,'r');
char * ligne;

if(fp==NULL) { ERROR_MSG("Impoosible d'ouvrir le fichier test ")}

else {


  while(fgets(ligne,128,fp)!=NULL)
  {

  		char * token=strtok(ligne,"");
  		sscanf(token,"%s",&definition.nom);
  		printf("\nNOM : %s\n");

  		token=strtok(NULL,"");
  		sscanf(token,"%c",definiton.type);
  		printf("\n TYPE : %s\n",definiton.type);

  		token=strtok(NULL,"");
  		sscanf(token,"%x",&definition.signature);
  		printf("\n SIGNATURE : %x\n",definition.signature);


  		token=strtok(NULL,"");
  		sscanf(token,"%x",&definition.masque);
  		printf("\n MASQUE: %x\n",definition.masque);


  		token=strtok(NULL,"");
  		sscanf(token,"%d",&definition.nmbr_oper);
  		printf("\n NBR OPERANDE : %d\n",definition.nmbr_oper);




  		
  		for (int i = 0; i < definition.nmbr_oper ; i++)
  			{	token=strtok(NULL,"");
  			char *temp;
  			sscanf(token,"%s",&definition.op_mapping[i]);
  			definition.op_mapping[i]=strdup(temp);
  			printf("\n OPERANDE : %s\n",definition.op_mapping[i]);
  			}
   }
}

}










































