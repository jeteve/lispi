CC=gcc
IFLAGS=-I../entree/
LFLAGS=-L../entree/
lexico.o : lexico.h lexico.c
	$(CC) -c -O2 $(IFLAGS) lexico.c
essai : essai.o lexico.o
	$(CC) -o essai $(LFLAGS)  essai.o lexico.o ../entree/entree.o
essai.o : essai.c
	$(CC) -c -O2 $(IFLAGS) essai.c
