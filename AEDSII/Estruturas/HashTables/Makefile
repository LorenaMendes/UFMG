IDIR   = include
CC     = clang
CFLAGS = -I$(IDIR)

DEPS   = Set.h RBT.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

IntArraySet: CompSetMain.o IntArraySet.o
	$(CC) -Wall -o IntArraySet CompSetMain.o IntArraySet.o -Iinclude.

BitArraySet: CompSetMain.o BitArraySet.o
	$(CC) -Wall -o BitArraySet CompSetMain.o BitArraySet.o -Iinclude.

HashSet: CompSetMain.o HashSet.o
	$(CC) -Wall -o HashSet CompSetMain.o HashSet.o -Iinclude.

NoEqualHashSet: CompSetMain.o NoEqualHashSet.o
	$(CC) -Wall -o NoEqualHashSet CompSetMain.o NoEqualHashSet.o -Iinclude.

RBTSet: RBT.o RedBlackSet.o CompSetMain.o
	$(CC) -Wall -o RBTSet RBT.o RedBlackSet.o CompSetMain.o -Iinclude.

.PHONY: clean

clean:
	rm -f *.o IntArraySet BitArraySet HashSet NoEqualHashSet RBTSet
