CC     = clang
CFLAGS =
ODIR   = obj

DEPS   = Tree.h

_OBJ = Tree.o

_OBJ_UN2 = Union2Main.o $(_OBJ)
OBJ_UN2 = $(patsubst %,$(ODIR)/%,$(_OBJ_UN2))

_OBJ_DEL = DelMain.o $(_OBJ)
OBJ_DEL = $(patsubst %,$(ODIR)/%,$(_OBJ_DEL))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

DelMain: $(OBJ_DEL)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

Union2Main: $(OBJ_UN2)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o DelMain Union2Main
