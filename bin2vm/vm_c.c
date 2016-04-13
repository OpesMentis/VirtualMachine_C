/*
	Programme n°2, interpretation des instructions binaires dans le fichier 'bin.txt'.
	Encodage : 5 bits  - fonction
			   5 bits  - parametre registre 1
			   1 bit   - flag (1 : reg ; 0 : imm)
			   16 bits - parametre o
			   5 bits  - parametre registre 2

	jmp et	 : 5 bits  - fonction
	autres du  5 bits  - non lus
	même type  1 bits  - flag
			   16 bits - parametre o
			   5 bits  - parametre registre

	braz et  : 5 bits  - fonction
	branz	   5 bits  - parametre registre
			   1 bit   - flag
			   16 bits - parametre o
			   5 bits  - non lus

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

	char * rslt = malloc(sizeof(char) * (b-a+1));
	strcpy(rslt, str);
	rslt[b] = '\0';
	return rslt+a;
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

// affiche le contenu d'une structure cmd
void print_cmd(struct cmd comm) {
	printf("%s\n", comm.fct);
	printf("%i\n", comm.r1);
	printf("%i\n", comm.flag);
	printf("%ld\n", comm.o);
	printf("%i\n\n", comm.r2);
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
			*pc = (regs[comm.r1] == 0)? o: (*pc)+1;
			break;
		case 16: // branz
			*pc = (regs[comm.r1] != 0)? o: (*pc)+1;
			break;
		case 17: // scall
			if (comm.flag == 0) {
				printf(">>> ");
				scanf("%i", regs+1);
			} else {
				printf("%i\n", *(regs+1));
			}
			(*pc)++;
			break;
		case 18: // stop
			printf("FIN DE L'EXÉCUTION\n");
			*pc = -1;
			break;
		default:
			printf("ERREUR À L'INSTRUCTION %i\n.", *pc);
			break;
	}
}

int main (int argc, char * argv[]) {

	int regs[NUM_REGS]; // registre
	int * pc = malloc(sizeof(int));			// program counter
	char * inst = malloc(32 * sizeof(char));
	struct cmd * comm = malloc(sizeof(struct cmd));
	FILE * code = NULL;

	*pc = 0;
	code = fopen("./../data/bin.txt", "r");

	while (*pc >= 0) {
		fscanf(code, "%32s", inst);
		inter(inst, comm);
		trait(*comm, regs, pc);
		fseek(code, 33 * (*pc), SEEK_SET);
	}

	fclose(code);

	/* Test manuel de trait -- satisfaisant
	regs[1] = 21;
	regs[2] = 7;

	printf("Après ini\n");
	printf("%i\n", regs[0]);
	printf("%i\n", regs[1]);
	printf("%i\n\n", regs[2]);

	inst = "00000000011000000000000001000000";
	inter(inst, comm);
	printf("Contenu de la commande.\n");
	print_cmd(*comm);
	trait(*comm, regs, pc);

	printf("Après exécution\n");
	printf("%i\n", regs[0]);
	printf("%i\n", regs[1]);
	printf("%i\n\n", regs[2]);
	*/

	return 0;
}
