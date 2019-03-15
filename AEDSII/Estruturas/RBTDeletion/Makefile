IDIR   = include
CC     = clang
CFLAGS = -I$(IDIR)

DEPS   = Set.h RBT.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

UnsortedArraySet: CompSetMain.o UnsortedArraySet.o
	$(CC) -Wall -o UnsortedArraySet CompSetMain.o UnsortedArraySet.o -I.

RedBlackSet: CompSetMain.o RBT.o RedBlackSet.o
	$(CC) -Wall -o RedBlackSet CompSetMain.o RBT.o RedBlackSet.o -I.

IsortArraySet: CompSetMain.o IsortArraySet.o
	$(CC) -Wall -o IsortArraySet CompSetMain.o IsortArraySet.o -I.

QsortArraySet: CompSetMain.o QsortArraySet.o
	$(CC) -Wall -o QsortArraySet CompSetMain.o QsortArraySet.o -I.

.PHONY: clean

clean:
	rm -f *.o UnsortedArraySet IsortArraySet QsortArraySet UnsortedArraySet RedBlackSet
