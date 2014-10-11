#include <stdio.h>
#include <string.h>

int cherche_deux_point(char * chaine)
{ int resultat; int i=0;
    while(resultat!=0&&i<strlen(chaine))
    {   printf("\n %s \n",&chaine[i]);
        if(chaine[i]==':') resultat=0;

        else {resultat=1;i++;}
    }
return resultat;
}


int main()
{ 

char * chaine1 = strdup("0xbeef:0xFFFF");
printf("\n %s \n",chaine1);

int res=cherche_deux_point(chaine1);

if(res==0) printf("\n on a trouver les : \n");
else printf("\n On a rien trouver\n") ;




char * sub;
sub=strtok(chaine1,"	 /t/n");
while(sub!=NULL)
{
printf("%s\n",sub);
        sub = strtok(NULL," /n/t	");
    }
    return 0;
}