#include<stdio.h>
#include <unistd.h>
#include "asmToBin.h"


int main (int argc, const char* argv[] ){

	char* name_file_in = "ex_code";
	char* name_file_out = "bin.txt";
	char* string = malloc(10000);
	fill_string(name_file_in, string);
	//write_file(name_file_out, string);
		
	}

int fill_string(char* name_file, char* string){
	FILE * fp;
    char * line_asm = NULL;
    char * line_bin = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(name_file, "r");
    if (fp == NULL)
        return 1;

    while ((read = getline(&line_asm, &len, fp)) != -1) {
    	//conversion asm to bin
    	convert(line_asm, line_bin);
        // ajout de la ligne au string
        
        strcat(string, line_bin);        
    }

    fclose(fp);
    if (line_asm)
        free(line_asm);
    if (line_bin)
        free(line_bin);    
    exit(0);
   }
    		    		
int convert(char* line_asm, char* line_bin){
	line_bin = strdup(line_asm);

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


