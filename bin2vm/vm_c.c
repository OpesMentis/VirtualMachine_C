/*
	Programme n°2, interpretation des instructions binaires dans le fichier 'bin.txt'.
	Encodage : 5 bits  - fonction
			   5 bits  - parametre registre 1
			   1 bit   - flag (1 : reg ; 0 : imm)
			   16 bits - parametre o
			   5 bits  - parametre registre 2

	jmp et	 : 5 bits  - fonction
	autres du  5 bits  - '00000'
	même type  1 bits  - flag
			   16 bits - parametre o
			   5 bits  - parametre registre

	scall    : 5 bits  - fonction (10001)
			   5 bits  - non lus
			   1 bit   - parametre (0, lecture clavier ; 1, affichage ; reg. 31)
			   21 bits - non lus



	Auteur : Antoine Planchot
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vm_c.h"

#define NUM_REGS 32

// extraire proprement des morceaux de chaine de caractere (Python - str[a:b])
char * extstr (char * str, int a, int b) {
	if (a > b || a < 0 || b >= strlen(str)+1) {
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
int bin2dec (char * bin) {
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

// convertit une instruction binaire dans une structure "cmd"
void inter (char * inst, struct cmd * comm) {
	strcpy(comm->fct, extstr(inst, 0, 5));
	comm->r1 = bin2dec(extstr(inst, 5, 10));
	comm->flag = bin2dec(extstr(inst, 10, 11));
	comm->o = bin2dec(extstr(inst, 11, 27));
	comm->r2 = bin2dec(extstr(inst, 27, 32));
}

// exécute une commande, pointeurs vers registre et pc donnés
void trait (struct cmd comm, int * regs, int * pc) {
	long o = (comm.flag == 1)? regs[comm.o]: comm.o;

	switch (bin2dec(comm.fct)) {
		case 0: // add
			regs[comm.r2] = regs[comm.r1] + o;
			(*pc)++;
			break;
		case 1: // sub
			regs[comm.r2] = regs[comm.r1] - o;
			(*pc)++;
			break;
		case 2: // mult
			regs[comm.r2] = regs[comm.r1] * o;
			(*pc)++;
			break;
		case 3: // div
			regs[comm.r2] = regs[comm.r1] / o;
			(*pc)++;
			break;
		case 4: // and
			regs[comm.r2] = regs[comm.r1] & o;
			(*pc)++;
			break;
		case 5: // or
			regs[comm.r2] = regs[comm.r1] | o;
			(*pc)++;
			break;
		case 6: // xor
			regs[comm.r2] = regs[comm.r1] ^ o;
			(*pc)++;
			break;
		case 7: // shl
			regs[comm.r2] = regs[comm.r1] << o;
			(*pc)++;
			break;
		case 8: // shr
			regs[comm.r2] = regs[comm.r1] >> o;
			(*pc)++;
			break;
		case 9: // slt
			regs[comm.r2] = (comm.r1 < o)? 1: 0;
			(*pc)++;
			break;
		case 10: // sle
			regs[comm.r2] = (comm.r1 <= o)? 1: 0;
			(*pc)++;
			break;
		case 11: // seq
			regs[comm.r2] = (comm.r1 == o)? 1: 0;
			(*pc)++;
			break;
		case 12: // load
			regs[comm.r2] = regs[comm.r1 + o];
			(*pc)++;
			break;
		case 13: // store
			regs[comm.r1 + o] = regs[comm.r2];
			(*pc)++;
			break;
		case 14: // jmp
			regs[comm.r2] = (*pc)+1;
			*pc = o;
			break;
		case 15: // braz
			*pc = (comm.r1 == 0)? o: (*pc)+1;
			break;
		case 16: // branz
			*pc = (comm.r1 != 0)? o: (*pc)+1;
			break;
		case 17: // scall
			if (comm.flag == 0) {
				scanf("%i", regs+1);
			} else {
				printf("%i", *(regs+1));
			}
			(*pc)++;
			break;
		case 18: // stop
			printf("FIN DE L'EXÉCUTION");
			break;
		default:
			printf("ERREUR À L'INSTRUCTION %i", *pc);
			break;
	}
}

int main (int argc, char * argv[]) {

	int regs[NUM_REGS]; // registre
	int * pc;			// program counter

	char * inst = malloc(32 * sizeof(char));
	struct cmd * comm = malloc(sizeof(struct cmd));
	FILE * code = NULL;

	code = fopen("./../data/bin.txt", "r");
	fscanf(code, "%32s", inst);
	inter(inst, comm);
	fscanf(code, "%32s", inst);
	inter(inst, comm);

	fclose(code);

	printf("%s\n", comm->fct);
	printf("%d\n", comm->r1);
	printf("%d\n", comm->flag);
	printf("%ld\n", comm->o);
	printf("%d\n", comm->r2);

	return 0;
}
