clean:	
	rm ../bin/*

debug: C/cfd.c C/cfd.h
	gcc -Wall -o ../bin/cfd -g C/cfd.c -lwiringPi

cfd:	C/cfd.c C/cfd.h
	gcc -o ../bin/cfd C/cfd.c -lwiringPi	
