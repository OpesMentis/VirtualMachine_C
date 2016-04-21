#include "asmToBin.h"
#include "util.h"


int main (int argc, const char* argv[] ){

	char* name_file_in = "../data/ex_code";
	char* name_file_out = "../data/bin.txt";
	char* string = malloc(10000);
	fill_string(name_file_in, string);
	write_file(name_file_out, string);
		
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
		convert_add(word_asm, line_asm, line_bin, word_bin);
    	 }
    	 else if(resTemp ==-1){
    	 	// on est dans le cas d'un jump
    	 convert_jump(word_asm, line_asm, line_bin, word_bin);
    	  	
    	  }
		 else if(resTemp ==-2){
    	 	// on est dans le cas d'un braz et branz
		convert_braz( word_asm, line_asm, line_bin, word_bin);
		
    	  }
    	   else if(resTemp ==-3){
    	   // on est dans le cas d'un scall
    	 convert_scall(word_asm, line_asm, line_bin, word_bin); 	
    	 	
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
      	     		
void convert_add( char* word_asm,  char* line_asm, char* line_bin, char* word_bin){

    	  	add_registre(word_asm, line_asm, line_bin, word_bin);
    	  	add_flag_argO( word_asm, line_asm, line_bin, word_bin);
    	  	add_registre(word_asm, line_asm, line_bin, word_bin);

}
void convert_jump( char* word_asm,  char* line_asm, char* line_bin, char* word_bin){

// on rajoute 5 bits  
    	  	strcpy(word_bin,"11111");
    	  	strcat(line_bin, word_bin); 
    	  	add_flag_argO(word_asm, line_asm, line_bin, word_bin);
    	  	add_registre(word_asm, line_asm, line_bin, word_bin);

}

void convert_braz( char* word_asm,  char* line_asm, char* line_bin, char* word_bin){
		  add_registre(word_asm, line_asm, line_bin, word_bin);
    	  add_flag_argO(word_asm, line_asm, line_bin, word_bin);

}


void convert_scall( char* word_asm,  char* line_asm, char* line_bin, char* word_bin){
// on rajoute 5 bits  
    	  	strcpy(word_bin,"11111");
    	  	// on rajoute le parametre de scall 
    	  	strcat(line_bin, word_bin); 
    	  	word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  convert_param1bit(word_asm, word_bin);
			strcat(line_bin, word_bin); 

}


void add_flag_argO(char* word_asm,  char* line_asm, char* line_bin, char* word_bin){
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
    	  	strcat(line_bin, word_bin);
    	  	// on rajoute le parametre O
    	  	memset(word_bin, 0, sizeof word_bin); 
    	  	convert_paramO(word_asm, word_bin);
			strcat(line_bin, word_bin); 
    	  	}
}

void add_registre(char* word_asm,  char* line_asm, char* line_bin, char* word_bin){
// On rajoute un registre
 	  		word_asm = strtok (NULL," ,");
			memset(word_bin, 0, sizeof word_bin);
    	  	if(convert_register(word_asm, word_bin)==0){
		strcat(line_bin, word_bin);
		}

}





