#include<stdio.h>
#include "asmToBin.h"


int main (int argc, const char* argv[] ){


		
	}

void read_file(){
			FILE *ptr_file;
    		char buf[1000];

    		ptr_file =fopen("input.txt","r");
    		if (!ptr_file)
        		return 1;

    		while (fgets(buf,1000, ptr_file)!=NULL)
        		printf("%s",buf);

		fclose(ptr_file);
    		return 0;
    		}
    		
void write_file(){
		FILE *ptr_file;
		int x;

		ptr_file =fopen("asm_program.txt", "r");

		if (!ptr_file)
			return 1;

		for (x=1; x<=10; x++)
			fprintf(ptr_file,"%d\n", x);

		fclose(ptr_file);

		return  0;

}    		

// Permet d'effacer les \n d'un chaîne de caractères
void clean(char *str, int length){
	int i;
	for(i =0; i<length; i++){
		if(str[i]=='\n'){
			str[i]='\0';
		}
	}
}
