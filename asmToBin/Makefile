all: crypt client serveur test_list
	
config.o: config.c config.h libtarga.o
	gcc -Wall -c config.c -o config.o

libtarga.o : libtarga.c libtarga.h
	gcc -Wall -c libtarga.c -o libtarga.o -std=c99

crypt.o : crypt.c crypt.h libtarga.o 
	gcc -Wall -c crypt.c -o crypt.o -std=c99
	
client.o: client.c client.h config.o
	gcc -Wall -c client.c -o client.o

serveur.o: serveur.c serveur.h config.o
	gcc -Wall -c serveur.c -o serveur.o

run.o: run.c serveur.o
	gcc -Wall -c run.c -o run.o

crypt: crypt.o libtarga.o
	gcc -Wall crypt.o libtarga.o -o crypt -std=c99
	mv crypt ../tests

client: client.o config.o libtarga.o
	gcc -Wall client.o config.o libtarga.o -o client
	cp client ../tests
	mv client ../client

serveur: run.o serveur.o config.o libtarga.o
	gcc -Wall run.o serveur.o config.o libtarga.o -o serveur
	cp serveur ../tests
	mv serveur ../serveur

test_list: serveur.o config.o libtarga.o
	gcc -Wall test_list.c serveur.o config.o libtarga.o -o test_list
	mv test_list ../tests

clean:
	rm -f *.o
	rm -f *.c~
	rm -f *.h~
	rm -f Makefile~

hardclean:
	make clean
	rm -rf ../client/* ../serveur/* ../tests/*
	cp -r ../Images ../serveur
	cp -r ../Images ../tests
	mkdir ../tests/imageCrypt
	cp ../Images/* ../tests/imageCrypt
	cp ../help.txt ../serveur
	
