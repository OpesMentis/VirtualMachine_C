all: asmToBin
	
asmToBin.o: asmToBin.c asmToBin.h asmToBin.o
	gcc -w -Wall -c asmToBin.c -o asmToBin.o



asmToBin: asmToBin.o 
	gcc -w -Wall asmToBin.o -o asmToBin -std=c99



#	cp client ../tests
#	mv client ../client


clean:
	rm -f *.o
	rm -f *.c~
	rm -f *.h~
	rm -f Makefile~

hardclean:
	make clean
	
	
