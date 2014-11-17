#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main ()
{
	char chaine[128];
	printf("Entrez un chaine\n");
	scanf("%s",chaine);

	void * adresse = &chaine;
	uint64_t adr = (uint64_t) adresse;

	//sprintf(adresse,"%p",&chaine);
	//sscanf(&chaine,"%p",&adresse);
	printf("adresse : %p ; adr = %llu \n",adresse,adr);
	//printf("sinon la vrai adresse pas trafiquer : %p \n",chaine);
	//printf("sinon la vrai adresse pas trafiquer : %p ",&chaine);
	printf(" mot : %s",adresse);


	void * adr2 = (void *) adr;
	printf("\n haha mot : %s",adr2);


}