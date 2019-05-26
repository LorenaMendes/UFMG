cc=gcc
Servers: Servers.o main.o
	gcc Servers.o main.o -o tp3h $(cflags)
main.o: main.c Servers.o
	gcc -c main.c $(cflags)
Servers.o: Servers.h Servers.c
	gcc -c Servers.c $(cflags)
clean:
	rm *.o *.gch
	rm block