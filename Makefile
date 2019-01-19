clean:	
	rm *.o

cfd:	cfd.c
	gcc -o cfd.o cfd.c -lwiringPi	
