/*
#include "fonction_token.h"

int main() {

char * i=calloc(MAX_STR,sizeof(&i));
char * j=calloc(MAX_STR,sizeof(&j));
char * k=calloc(MAX_STR,sizeof(&k));
char * l=calloc(MAX_STR,sizeof(&l));
i=strdup("0xFF");
j=strdup("0x25");
l=strdup("0xEEEEEEEEEEEFFFFFFFFFFFFFFFFFFFFFFFF");
k=strdup("0x5T67ZRT");

// Test de la v1 de is_hexa
puts("---------------------------------------------------------------------------------------");
puts("Testons si les valeurs suivantes sont hexadecimales avec la version V1 : ");puts("");
puts("---------------------------------------------------------------------------------------");

printf("	i: %s		j: %s		k: %s	l: %s",i,j,k,l);puts("");
	if(is_hexa_v1(i)!=0) {puts("");printf(" i est hexadecimal");puts("");}
			else {puts("");printf("i n'est pas hexa");puts("");}
	if(is_hexa_v1(j)!=0) {puts("");printf(" j est hexadecimal");puts("");}
			else {puts("");printf("j n'est pas hexa");puts("");}
	if(is_hexa_v1(k)!=0) {puts("");printf(" k est hexadecimal, C'EST PAS NORMAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");puts("");}
			else {puts("");printf("k n'est pas hexa");puts("");}	
	if(is_hexa_v1(l)!=0) {puts("");printf(" l est hexadecimal, C'EST PAS NORMAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");puts("");}
			else {puts("");printf("l n'est pas hexa");puts("");}
*/
 //Test de lettre_hexa
			/*
puts("---------------------------------------------------------------------------------------");
puts("---------------------------------------------------------------------------------------");
puts("Testons si les lettre  sont hexadecimales : ");puts("");
puts("---------------------------------------------------------------------------------------");
puts("---------------------------------------------------------------------------------------");
printf("	i: %s 		j: %s 		k: %s    	l: %s",i,j,k,l);puts("");
	if(lettre_hexa(i)==0) {puts("");printf(" i a les bonnes lettre de l'hexa");puts("");}
			else {puts("");printf("i n'a pas les bonnes lettre de l'hexa");puts("");}
	if(lettre_hexa(j)==0) {puts("");printf(" j a les bonnes lettre de l'hexa");puts("");}
			else {puts("");printf("j n'a pas les bonnes lettre de l'hexa");puts("");}
     if(lettre_hexa(k)==0) {puts("");printf(" k a les bonnes lettre de l'hexa");puts("");}
			else {puts("");printf("k n'a pas les bonnes lettre de l'hexa");puts("");}
	if(lettre_hexa(l)==0) {puts("");printf(" l a les bonnes lettre de l'hexa");puts("");}
			else {puts("");printf("l n'a pas les bonnes lettre de l'hexa");puts("");}


//  test de la v2 de is_hexa

puts("\n \n---------------------------------------------------------------------------------------");
puts(" Testons si les valeurs suivantes sont hexadecimales avec la version v2 : \n ");
puts("---------------------------------------------------------------------------------------");



printf("	i: %s		j: %s		k: %s		l: %s \n",i,j,k,l);
	if(is_hexa_v2(i)==0) printf(" \n i est hexadecimal \n");
			else printf(" \n i n'est pas hexa  C'EST PAS NORMAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
	if(is_hexa_v2(j)==0) printf("\n j est hexadecimal \n");
			else printf(" \n j n'est pas hexa  C'EST PAS NORMAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
	if(is_hexa_v2(k)==0) printf(" \n k est hexadecimal  C'EST PAS NORMAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
			else printf(" \n k n'est pas hexa \n");
	if(is_hexa_v2(l)==0) printf("\n l est hexadecimal  C'EST PAS NORMAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
			else printf(" \n l n'est pas hexa \n");

// test de inf_8 pour cela on introduit de nouveaux test !!!


i=strdup("028923423");
j=strdup("02131441");
k=strdup("1223122212");

puts("---------------------------------------------------------------------------------------");
puts("---------------------------------------------------------------------------------------");
puts("Testons si les chiffre  sont supérieur à 8 : \n");
puts("---------------------------------------------------------------------------------------");
puts("---------------------------------------------------------------------------------------");
printf("	i: %s 		j: %s 		k: %s    	",i,j,k);puts("");
	if(inf_8(i)==0) printf(" \n i n'a de chiffre plus grand que 8 \n");
			else    printf("\n i a des chiffres plus grand que 8 \n");
	if(inf_8(j)==0) printf(" \n j n'a pas de chiffres plus grand que 8 \n");
			else printf(" \n j a des chiffres plus grand que 8 \n");
     if(inf_8(k)==0) printf(" \n k n'a de chiffre plus grand que 8 \n");
			else printf("\n k a des chiffres plus grand que 8 \n");
	

puts("---------------------------------------------------------------------------------------");
puts("---------------------------------------------------------------------------------------");
puts("Testons si les chiffre  sont supérieur à 8 : \n");
puts("---------------------------------------------------------------------------------------");
puts("---------------------------------------------------------------------------------------");
printf("	i: %s 		j: %s 		k: %s    	",i,j,k);puts("");
	if(is_octal(i)==0) printf(" \n i est octal \n");
			else    printf("\n i n'est pas octal \n");
	if(is_octal(j)==0) printf(" \n j est octal \n");
			else printf(" \n j n'est pas octal \n");
     if(is_octal(k)==0) printf(" \n k est octal \n");
			else printf("\n k n'est octal \n");











}


*/
