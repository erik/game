#Fixme: write

CC=clang
CFLAGS=  -Wall -Wextra -std=c99 -Wno-unused-parameter -g
LNFLAGS= -lSDL -lSDL_image
SRC=$(wildcard src/*.c)
HEAD=$(wildcard src/*.h)
OBJ=$(SRC:.c=.o)
EXE=game

all: $(OBJ) $(HEAD)
	$(CC) $(OBJ) $(CFLAGS) $(LNFLAGS) -o$(EXE)

debug: clean
	$(MAKE all $(CFLAGS += -g))

main.o: src/main.c
util.o: src/util.c

clean:
	rm -f src/*.o
	rm -f $(EXE)

.c.o:
	@echo "   cc $<"
	@${CC} -c ${CFLAGS} $< -o $@

todo:
	@find src -type f | xargs grep -n -i "TODO"
	@find src -type f | xargs grep -n -i "FIXME"

loc: 
	@wc -l src/*.[ch]

# requires sloccount
sloc:
	@sloccount src lib | grep '(SLOC)'


.PHONY= loc sloc todo
