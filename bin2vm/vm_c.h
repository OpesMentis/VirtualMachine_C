#ifndef VMCH
#define VMCH

struct cmd {
	char fct[5];
	int r1;
	int r2;
	int flag;
	long o;
};

char * extstr (char * str, int a, int b);
int bin2dec (char * bin);
void inter (char * inst, struct cmd * comm);
void print_cmd(struct cmd comm);
void trait (struct cmd comm, int * regs, int * data, int * pc);

#endif
