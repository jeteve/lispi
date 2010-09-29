CC=gcc
entree.o : entree.h entree.c
	$(CC) -c  -O2 entree.c

essai : essai.o entree.o
	$(CC) -o essai essai.o entree.o
essai.o : essai.c
	$(CC) -c  -O2 essai.c


clean :	
	rm -f *.o *~
