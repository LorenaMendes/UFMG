IDIR   = include
CC     = clang
CFLAGS = -g -I$(IDIR)

DEPS   = Tree.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Trie: TestTrieMain.o Trie.o
	$(CC) -Wall -o TrieMain TestTrieMain.o Trie.o -I.

BinT: TestTrieMain.o BinT.o
	$(CC) -Wall -o BinTMain TestTrieMain.o BinT.o -I.

RBT: TestTrieMain.o RBT.o
	$(CC) -Wall -o RBTMain TestTrieMain.o RBT.o -I.

TrieComp: CompTreesMain.o Trie.o
	$(CC) -Wall -o TrieComp CompTreesMain.o Trie.o -I.

BinTComp: CompTreesMain.o BinT.o
	$(CC) -Wall -o BinTComp CompTreesMain.o BinT.o -I.

RBTComp: CompTreesMain.o RBT.o
	$(CC) -Wall -o RBTComp CompTreesMain.o RBT.o -I.

.PHONY: clean

clean:
	rm -f *.o TrieMain BinTMain RBTMain CompTreesMain
