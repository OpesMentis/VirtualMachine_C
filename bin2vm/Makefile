all: vm_c.exe

vm_c.exe: vm_c.o
	gcc -o vm_c.exe vm_c.o

vm_c.o: vm_c.c vm_c.h
	gcc -c vm_c.c

clean:
	rm vm_c.exe vm_c.o
