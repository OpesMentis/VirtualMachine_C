all: asmToBin.exe
	
asmToBin.o: asmToBin.c asmToBin.h util.o
	gcc -w -Wall -o asmToBin.o -c asmToBin.c -lm -lc -std=c99

util.o: util.c util.h
	gcc -w -Wall -o util.o -c util.c -lm -lc -std=c99

asmToBin: asmToBin.o util.o
	gcc -w -Wall -o asmToBin.exe asmToBin.o util.o -lm -lc -std=c99



#	cp client ../tests
#	mv client ../client


clean:
	rm -f *.o
	rm -f *.c~
	rm -f *.h~
	rm -f Makefile~

hardclean:
	make clean
	
	
