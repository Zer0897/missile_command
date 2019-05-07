IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

LDIR=lib
SDIR=src
ODIR=obj
TARGET=target

LIBS=-lncurses -lm

_DEPS = mainloop.h input_layer.h animate.h canvas.h alien_layer.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o mainloop.o input_layer.o animate.o canvas.o alien_layer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

missile_command: $(OBJ)
	$(CC) -o $(TARGET)/$@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
