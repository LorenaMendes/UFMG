CC     = clang
CFLAGS =
ODIR   = obj

DEPS   = Tree.h

_OBJ = Tree.o

_OBJ_VIS = VisMain.o $(_OBJ)
OBJ_VIS = $(patsubst %,$(ODIR)/%,$(_OBJ_VIS))

_OBJ_DOT = DotMain.o $(_OBJ)
OBJ_DOT = $(patsubst %,$(ODIR)/%,$(_OBJ_DOT))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

VisMain: $(OBJ_VIS)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

DotMain: $(OBJ_DOT)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o VisMain DotMain
