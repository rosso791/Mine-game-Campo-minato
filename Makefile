
matrice: matrice.o stackCella.o 
	gcc --pedantic matrice.o stackCella.o  -o matrice

matrice.o: matrice.c matrice.h stackCella.h
	gcc --ansi --pedantic -c matrice.c -o matrice.o

stackCella.o: stackCella.c stackCella.h
	gcc --ansi --pedantic -c stackCella.c -o stackCella.o
