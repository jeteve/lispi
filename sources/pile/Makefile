
pile.o : pile.c pile.h
	gcc -I. -c pile.c
clean :
	rm -f *.o *~
calc : calc.o pile.o
	gcc -I. -o calc calc.o pile.o

calc.o : calc.c
	gcc -I. -c calc.c


test_pile : test_pile.o pile.o
	gcc -I. -o  test_pile test_pile.o pile.o
test_pile.o : test_pile.c
	gcc -I. -c test_pile.c