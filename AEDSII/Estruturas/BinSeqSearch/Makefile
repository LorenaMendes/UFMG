CC     = clang
CFLAGS =

ODIR=obj

DEPS = Search.h

_OBJ = Search.o

_OBJ_BIN = BinMain.o $(_OBJ)
OBJ_BIN = $(patsubst %,$(ODIR)/%,$(_OBJ_BIN))

_OBJ_SEQ = SeqMain.o $(_OBJ)
OBJ_SEQ = $(patsubst %,$(ODIR)/%,$(_OBJ_SEQ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

BinMain: $(OBJ_BIN)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

SeqMain: $(OBJ_SEQ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
