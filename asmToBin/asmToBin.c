#include<stdio.h>
#include <unistd.h>
#include "asmToBin.h"


int main (int argc, const char* argv[] ){

	char* name_file_in = "../data/ex_code";
	char* name_file_out = "../data/bin.txt";
	char* string = malloc(10000);
	fill_string(name_file_in, string);
	write_file(name_file_out, string);
		
	}

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

int fill_string(char* name_file, char* string){
	FILE * fp;
	char temp[100];
	memset(temp, 0, sizeof temp);
    char* line_asm = NULL;
    char line_bin[100];
    char* word_asm = NULL;
    char word_bin[100];
    size_t len = 0;
    ssize_t read;
    int resTemp;
	
    fp = fopen(name_file, "r");
    if (fp == NULL)
        return 1;

    while ((read = getline(&line_asm, &len, fp)) != -1) {
    	
  	  // on enléve \n et on split la ligne 
  	 line_asm[strlen(line_asm)-1] = 0; 
	 word_asm = strtok (line_asm," ,");
 		/* -1 pour jmp et autre du même style
	-2 braz et branz
	-3 pour scall
	-4 pour stop
	0 cmd normale
	1 rien reconnu
*/ 
    	// first the command pour tout le monde
    	resTemp = convert_cmd(word_asm, word_bin);
    	strcat(line_bin, word_bin);
    	
    	
    	if(resTemp ==0){
    	// on est dans le cas d'un add
		// On rajoute un registre
 	  		word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_register(word_asm, word_bin)==0){
		strcat(line_bin, word_bin);
		}
    	  	// on rajoute le flag
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_flag(word_asm, word_bin)==0){
    	  	strcat(line_bin, word_bin); 
    	  	// on rajoute le parametre O
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
			convert_paramO(word_asm, word_bin);
			strcat(line_bin, word_bin); 
    	  	}
    	  	else{
    	  	convert_paramO(word_asm, word_bin);
			strcat(line_bin, word_bin); 
    	  	}
    	  	// on rajoute le registre
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_register(word_asm, word_bin)==0){
		strcat(line_bin, word_bin);
		}
    	 }
    	 else if(resTemp ==-1){
    	 	// on est dans le cas d'un jump
    	 	// on rajoute 5 bits  
    	  	strcpy(word_bin,"88888");
    	  	strcat(line_bin, word_bin); 
    	  	// on rajoute le flag
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_flag(word_asm, word_bin)==0){
    	  	strcat(line_bin, word_bin); 
    	  	// on rajoute le parametre O
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
			convert_paramO(word_asm, word_bin);
			strcat(line_bin, word_bin); 
    	  	}
    	  	else{
    	  	convert_paramO(word_asm, word_bin);
			strcat(line_bin, word_bin); 
    	  	}
    	  	// on rajoute le registre
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_register(word_asm, word_bin)==0){
		strcat(line_bin, word_bin);
		}
    	  	
    	  }
		 else if(resTemp ==-2){
    	 	// on est dans le cas d'un braz et branz
		// On rajoute un registre
 	  		word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_register(word_asm, word_bin)==0){
		strcat(line_bin, word_bin);
		}
    	  	// on rajoute le flag
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_flag(word_asm, word_bin)==0){
    	  	strcat(line_bin, word_bin); 
    	  	// on rajoute le parametre O
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
			convert_paramO(word_asm, word_bin);
			strcat(line_bin, word_bin); 
    	  	}
    	  	else{
    	  	convert_paramO(word_asm, word_bin);
			strcat(line_bin, word_bin); 
    	  	}
		
    	  }
    	   else if(resTemp ==-3){
    	   // on est dans le cas d'un scall
    	 	// on rajoute 5 bits  
    	  	strcpy(word_bin,"88888");
    	  	strcat(line_bin, word_bin); 
    	  	// on rajoute le parametre
    	  word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
			 convert_param1bit(word_asm, word_bin);
			 strcat(line_bin, word_bin); 
    	 	
    	  }
  		// on complete avec des 0 si besoin
  		
		// on complete si besoin
		if( strlen(line_bin) <32){
	int diff = 32-strlen(line_bin);
	while(diff >0){
	strcat(temp, "0");
	diff--;
	}
	}
        // ajout de la ligne au string    
        strcat(line_bin, temp);  
        strcat(string, line_bin);
       	strcat(string, "\n");
       	
       	
       	memset(temp, 0, sizeof temp);
       	memset(line_bin, 0, sizeof line_bin);
    }       


    fclose(fp);
  

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
	printf("Ligne: %s\n", line_asm);
	printf("Conversion dec %d to bin: %s\n", a,binary);
	printf("Diff pour 0: %d\n", diff);
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



