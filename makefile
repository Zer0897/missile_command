IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

LDIR=lib
SDIR=src
ODIR=obj
TARGET=target

LIBS=-lncurses

_DEPS = mainloop.h input.h vector.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o mainloop.o input.o vector.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

missile_command: $(OBJ)
	$(CC) -o $(TARGET)/$@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
