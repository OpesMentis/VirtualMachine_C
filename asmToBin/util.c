#include "util.h"

long decimalToBinary(long n) {
    int remainder; 
    long binary = 0, i = 1;
     
    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}

void convert_param1bit(char* word_asm,char* word_bin){
	
if (strcmp(word_asm, "0") == 0) strcpy(word_bin,"0");
else if (strcmp(word_asm, "1") == 0) strcpy(word_bin,"1");

}

int convert_flag(char* line_asm, char* line_bin){
 
	if (strcmp(line_asm, "imm") == 0) {
	strcpy(line_bin,"0");
	 return 0;
	 }
	else {
	strcpy(line_bin,"1");
	 return 1;
	 }
}


int convert_register(char* line_asm, char* line_bin){
	
	int diff;
	const char *end;
	int a = strtol(line_asm, end, 10);
	char temp[100];
	char binary[100];
	sprintf(binary, "%d", decimalToBinary(a));
	
	// ajout des 0 si besoin
	if( strlen(binary) <5){
	diff = 5-strlen(binary);
	while(diff >0){
	strcat(temp, "0");
	diff--;
	}
	}
	strcat(temp, binary);
	strcpy(line_bin, temp);
	
   return 0;
   
}


int convert_paramO(char* line_asm, char* line_bin){
	int diff;
	const char *end;
	int a = strtol(line_asm, end, 10);
	char temp[100];
	char binary[100];
	sprintf(binary, "%d", decimalToBinary(a));
	
	// ajout des 0 si besoin
	if( strlen(binary) <16){
	diff = 16-strlen(binary);
	while(diff >0){
	strcat(temp, "0");
	diff--;
	}
	}
	strcat(temp, binary);
	strcpy(line_bin, temp);
	
   return 0;

}


/* -1 pour jmp et autre du même style
	-2 braz et branz
	-3 pour scall
	-4 pour stop
	0 cmd normale
	1 rien reconnu
*/ 
   
int convert_cmd(char* line_asm, char* line_bin){


	if (strcmp(line_asm, "nop") == 0) 
	{
		strcpy(line_bin,"00000");
		return 0;
	} 
	else if (strcmp(line_asm, "add") == 0)
	{
		strcpy(line_bin,"00001");
		return 0;
	}
	else if (strcmp(line_asm, "sub") == 0)
	{
		strcpy(line_bin,"00010");
		return 0;
	}
	else if (strcmp(line_asm, "mult") == 0)
	{
		strcpy(line_bin,"00011");
		return 0;
	}
	else if (strcmp(line_asm, "div") == 0)
	{
		strcpy(line_bin,"00100");
		return 0;
	}
	else if (strcmp(line_asm, "and") == 0)
	{
		strcpy(line_bin,"00101");
		return 0;
	}
	else if (strcmp(line_asm, "or") == 0)
	{
		strcpy(line_bin,"00110");
		return 0;
	}
	else if (strcmp(line_asm, "xor") == 0)
	{
		strcpy(line_bin,"00111");
		return 0;
	}
	else if (strcmp(line_asm, "shl") == 0)
	{
		strcpy(line_bin,"01000");
		return 0;
	}
	else if (strcmp(line_asm, "shr") == 0)
	{
		strcpy(line_bin,"01001");
		return 0;
	}
	else if (strcmp(line_asm, "slt") == 0)
	{
		strcpy(line_bin,"01010");
		return 0;
	}
	else if (strcmp(line_asm, "sle") == 0)
	{
		strcpy(line_bin,"01011");
		return 0;
	}
	else if (strcmp(line_asm, "seq") == 0)
	{
		strcpy(line_bin,"01100");
		return 0;
	}
	else if (strcmp(line_asm, "load") == 0)
	{
		strcpy(line_bin,"01101");
		return 0;
	}
	else if (strcmp(line_asm, "store") == 0)
	{
		strcpy(line_bin,"01110");
		return 0;
	}
	else if (strcmp(line_asm, "jmp") == 0)
	{
		strcpy(line_bin,"01111");
		return -1;
	}
	else if (strcmp(line_asm, "braz") == 0)
	{
		strcpy(line_bin,"10000");
		return -2;
	}
	else if (strcmp(line_asm, "branz") == 0)
	{
		strcpy(line_bin,"10001");
		return -2;
	}
	else if (strcmp(line_asm, "scall") == 0)
	{

		strcpy(line_bin,"10010");
		return -3;
	}
	else if (strcmp(line_asm, "stop") == 0)
	{
		strcpy(line_bin,"10011");
		return -4;
	}
	else 
	{
		return 1;
	}
	
} 


		    		
int write_file (char *filepath, char *data) {
    int rc = 0;
	
    FILE *fOut = fopen (filepath, "w");
    if (fOut != NULL) {
        if (fputs (data, fOut) != EOF) {
            rc = 0;
        }
        fclose (fOut); // or for the paranoid: if (fclose (fOut) == EOF) rc = 0;
    }

    return rc;
}







