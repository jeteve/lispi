IFLAGS=-I../entree/ -I../lexico/ -I../doublet/ -I../symboles/ -I../utiles/ -I../fnum/ -I../eval/
OBJECTS=syntax.o ../lexico/lexico.o ../entree/entree.o \
	../symboles/symboles.o ../doublet/doublet.o ../utiles/utiles.o \
	../eval/eval.o  ../fnum/fnum.o ../flist/flist.o ../pile/pile.o
CC=gcc
syntax.o : syntax.h syntax.c
	$(CC) -c  -O2 $(IFLAGS) syntax.c


essai_e : essai_e.o syntax.o
	$(CC) -o essai_e $(IFLAGS) essai_e.o  $(OBJECTS)

essai_e.o : essai_e.c
	$(CC) -c  -O2 -Wall $(IFLAGS) essai_e.c ;
clean :
	rm -rf *.o *~ 
