/*
	Programme n°2, interpretation des instructions en binaire dans le fichier 'bin.txt'.
	Encodage : 5 bits  - fonction
			   5 bits  - parametre registre 1
			   1 bit   - flag o (1 : reg ; 0 : imm)
			   16 bits - parametre o
			   5 bits  - parametre registre 2
			   
	jmp		 : 5 bits  - fonction (01111)
			   1 bits  - flag o
			   16 bits - parametre o
			   5 bits  - parametre registre

	Auteur : Antoine Planchot
*/

#include <stdlib.h>
#include <stdio.h>

#define NUM_REGS 32

// extraire proprement des morceaux de chaine de caractere (Python - str[a:b])
char * extr_string (char * str, int a, int b) {
	
	if (a > b || a < 0 || b >= sizeof(str) / sizeof(char)) {
		printf("Erreur de bornes.\n");
		exit(0);
	}
	
	char * rslt;
	rslt = malloc(sizeof(char) * (b-a+1));
	int i;
	
	for (i = a; i < b; i++) {
		rslt[i-a] = str[i];
	}
	
	return rslt;
}

void inter (char * inst, char * fct, int * r1, int * r2, long * o) {
	// test de coherence
}
	

int main (int argc, char * argv[]) {
	
	int regs[NUM_REGS];
	FILE * code = NULL;

	code = fopen("bin.txt", "r");
	
	char * str1 = "0123456789";
	char * str2 = extr_string(str1, 2, 7);
	
	printf("%s\n", str2);
	
	return 0;
}
