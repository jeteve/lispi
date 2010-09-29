CC=gcc
CFLAGS=-c -O2
doublet.o : doublet.h doublet.c
	$(CC) $(CFLAGS) doublet.c
essai : essai.o doublet.o
	$(CC) -o essai   essai.o doublet.o 
test.o : test.c
	$(CC)  $(CFLAGS) test.c
clean :
	rm -f *.o *~
