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
char * extstr (char * str, int a, int b) {
	
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

// convertit un nombre binaire ('1001001110') en décimal
int bin2dec(char * bin) {
	return 0;
}

void inter (char * inst, char * fct, int * r1, int * r2, long * o) {
	// test de coherence
	if ((sizeof(inst) / sizeof(char) != 32 && strcmp(extstr(inst, 0, 5), "01111") != 1) || (sizeof(inst) / sizeof(char) != 27 && strcmp(extstr(inst, 0, 5), "01111") == 1) {
		System.out.println("Instruction corrompue.");
		exit(0);
	}
	
	*fct = extstr(inst, 0, 5);
	
	 
}
	

int main (int argc, char * argv[]) {
	
	int regs[NUM_REGS];
	FILE * code = NULL;

	code = fopen("bin.txt", "r");
	
	return 0;
}
