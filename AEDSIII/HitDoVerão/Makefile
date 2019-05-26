cc=gcc
ListaDeAdjacencia: ListaDeAdjacencia.o main.o
	gcc ListaDeAdjacencia.o main.o -o tp0 $(cflags)
main.o: main.c ListaDeAdjacencia.o
	gcc -c main.c $(cflags)
ListaDeAdjacencia.o: ListaDeAdjacencia.h ListaDeAdjacencia.c
	gcc -c ListaDeAdjacencia.c $(cflags)
clean:
	rm *.o *.gch
	rm block