#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ** init_tab_registre()
{ char** tab_compar;
    int i;
  tab_compar=calloc(70,sizeof(*tab_compar));
  if (tab_compar==NULL) return NULL;
  else 
  {
     for (i=0 ; i<70 ; i++) 
        {
       tab_compar[i]=calloc(64,sizeof (**tab_compar));
       if (tab_compar[i]== NULL) return NULL;

        }        
    }

    printf("\n TABLEAU INITIALISE\n");


    strcpy(tab_compar[0],"$0");                      strcpy(tab_compar[35],"$zero");                  
    strcpy(tab_compar[1],"$1");                      strcpy(tab_compar[36],"$at");            
    strcpy(tab_compar[2],"$2");                      strcpy(tab_compar[37],"$v0"); 
    strcpy(tab_compar[3],"$3");                      strcpy(tab_compar[38],"$v1");
    strcpy(tab_compar[4],"$4");                      strcpy(tab_compar[39],"$a0");
    strcpy(tab_compar[5],"$5");                      strcpy(tab_compar[40],"$a1");
    strcpy(tab_compar[6],"$6");                      strcpy(tab_compar[41],"$a2");
    strcpy(tab_compar[7],"$7");                      strcpy(tab_compar[42],"$a3");
    strcpy(tab_compar[8],"$8");                      strcpy(tab_compar[43],"$t0");
    strcpy(tab_compar[9],"$9");                      strcpy(tab_compar[44],"$t1");
    strcpy(tab_compar[10],"$10");                    strcpy(tab_compar[45],"$t2");
    strcpy(tab_compar[11],"$11");                    strcpy(tab_compar[46],"$t3");
    strcpy(tab_compar[12],"$12");                    strcpy(tab_compar[47],"$t4");
    strcpy(tab_compar[13],"$13");                    strcpy(tab_compar[48],"$t5");
    strcpy(tab_compar[14],"$14");                    strcpy(tab_compar[49],"$t6");
    strcpy(tab_compar[15],"$15");                    strcpy(tab_compar[50],"$t7");
    strcpy(tab_compar[16],"$16");                    strcpy(tab_compar[51],"$s0");
    strcpy(tab_compar[17],"$17");                    strcpy(tab_compar[52],"$s1");
    strcpy(tab_compar[18],"$18");                    strcpy(tab_compar[53],"$s2");
    strcpy(tab_compar[19],"$19");                    strcpy(tab_compar[54],"$s3");
    strcpy(tab_compar[20],"$20");                    strcpy(tab_compar[55],"$s4");
    strcpy(tab_compar[21],"$21");                    strcpy(tab_compar[56],"$s5");
    strcpy(tab_compar[22],"$22");                    strcpy(tab_compar[57],"$s6");
    strcpy(tab_compar[23],"$23");                    strcpy(tab_compar[58],"$s7");
    strcpy(tab_compar[24],"$24");                    strcpy(tab_compar[59],"$t8");
    strcpy(tab_compar[25],"$25");                    strcpy(tab_compar[60],"$t9");
    strcpy(tab_compar[26],"$26");                    strcpy(tab_compar[61],"$k0");
    strcpy(tab_compar[27],"$27");                    strcpy(tab_compar[62],"$k1");
    strcpy(tab_compar[28],"$28");                    strcpy(tab_compar[63],"$gp");
    strcpy(tab_compar[29],"$29");                    strcpy(tab_compar[64],"$sp");
    strcpy(tab_compar[30],"$30");                    strcpy(tab_compar[65],"$fp");
    strcpy(tab_compar[31],"$31");                    strcpy(tab_compar[66],"$ra");
    strcpy(tab_compar[32],"$32");                    strcpy(tab_compar[67],"$HI");
    strcpy(tab_compar[33],"$33");                    strcpy(tab_compar[68],"$LO");
    strcpy(tab_compar[34],"$33");                    strcpy(tab_compar[69],"$PC");

return tab_compar;
}

void aff(char **m, int b)
{int j;
    for(j=0;j<b;j++)
    {printf(" %s     " ,m[j]);}
}




// Retourne 0 si les registres existent 1 sinon

int reg_exist(char * reg1,char ** tab_tout_reg)
{ int j=0;int erreur=1;
    while(j<69&&erreur!=0)
    {
        if(strcmp(reg1,tab_tout_reg[j])==0)  erreur=0;
        else j++;
    }
    return erreur;
}


char** init_matrice()
{int i; char ** p;
    p=calloc(70,sizeof(*p));
    if (p==NULL) return NULL;
    else
    {
        for (i=0 ; i<70 ; i++)
        {
            p[i]=calloc(64,sizeof (**p));
            if (p[i]== NULL) return NULL;
            
        }
    }
    return p;}



int main() {
    char ** tab_reg=init_tab_registre();
    char ** tab_dem=init_matrice();
    tab_dem[0] = strdup("aaaaaaaaa");
    tab_dem[1] = strdup("$0");
    tab_dem[2] = strdup("$1");
    tab_dem[3] = strdup("1");
    tab_dem[4] = strdup("$v0");
    tab_dem[5] = strdup("haha");
    
    for(int i=0;i<6;i++)
    {printf("\n ON RECHERCHE LE REGISTRE %s \n",tab_dem[i]);
    int verif=reg_exist(tab_dem[i],tab_reg);

    if(verif==0) printf("\n LE REGISTRE EXISTE \n");
        else printf("\n LE REGISTRE EXISTE PAS !");
    }
}

