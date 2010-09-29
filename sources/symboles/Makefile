CFLAGS=-D_NO_DEBUG -c -O2 
symboles.o : symboles.h symboles.c
	gcc $(CFLAGS) symboles.c

essai : essai.o symboles.o
	gcc -o essai essai.o symboles.o

essai.o : essai.c
	gcc $(CFLAGS) essai.c

essai_i : essai_i.o symboles.o
	gcc -o essai_i  -I../entree/ -I../lexico/ essai_i.o ../entree/entree.o ../lexico/lexico.o symboles.o

essai_i.o : essai_i.c
	gcc $(CFLAGS) -I../entree/ -I../lexico/ essai_i.c
clean :
	rm -rf  *.o *~
