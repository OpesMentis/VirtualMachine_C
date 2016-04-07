/*
	Programme n°2, interpretation des instructions en binaire dans le fichier 'bin.txt'.
	Encodage : 5 bits  - fonction
			   5 bits  - parametre registre 1
			   1 bit   - flag o (1 : reg ; 0 : imm)
			   16 bits - parametre o
			   5 bits  - parametre registre 2

	jmp		 : 5 bits  - fonction (01111)
			   5 bits  - '00000'
			   1 bits  - flag o
			   16 bits - parametre o
			   5 bits  - parametre registre


	Auteur : Antoine Planchot
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	int val = 1;
	int tot = 0;
	int i;

	for (i = strlen(bin)-1; i >= 0; i--) {
		if (bin[i] == '1') {
			tot += val;
		}
		val *= 2;
	}

	return tot;
}

// interprète une ligne d'instruction en binaire
void inter (char * inst, char * fct, int * r1, int * r2, char flag, long * o) {
	// test de coherence
	if (strlen(inst) != 32) {
		printf("Instruction corrompue.");
		exit(0);
	}

	fct = extstr(inst, 0, 5);
	*r1 = bin2dec(extstr(inst, 5, 10));
	*flag = extstr(inst, 10, 11);
	*o = bin2dec(extstr(inst, 11, 27));
	*r2 = bin2dec(extstr(inst, 27, 32));
}


int main (int argc, char * argv[]) {

	int regs[NUM_REGS];
	FILE * code = NULL;

	code = fopen("./../data/bin.txt", "r");

	/*
	char * test = "101111";

	printf("%s -> %i\n", test, bin2dec(test));
	printf("Ca va ?\n");
	*/

	return 0;
}
