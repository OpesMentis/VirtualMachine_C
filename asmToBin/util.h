#include<stdio.h>
#include <unistd.h>

long decimalToBinary(long n);
void convert_param1bit(char* word_asm,char* word_bin);
int convert_flag(char* line_asm, char* line_bin);
int convert_register(char* line_asm, char* line_bin);
int convert_paramO(char* line_asm, char* line_bin);
int convert_cmd(char* line_asm, char* line_bin);
int write_file (char *filepath, char *data);
