# Makefile

INC_PATH=$(NCURSES_PATH)/include/
LIB_PATH=$(NCURSES_PATH)/lib/

CC=gcc
SOBJS=server.o
TOBJS=tetris.o print.o tetris_data.o
SOUT=server
TOUT=tetris
CFLAGS=-I$(INC_PATH)\
	-L$(LIB_PATH)\
	-lncurses
all: server tetris

server: $(SOBJS)
	$(CC) -o $(SOUT) $(SOBJS) $(CFLAGS)

tetris: $(TOBJS)
	$(CC) -o $(TOUT) $(TOBJS) $(CFLAGS)

server.o: server.c data.h
	$(CC) -c server.c $(CFLAGS)

tetris.o: tetris.c data.h print.h
	$(CC) -c tetris.c $(CFLAGS)

print.o: print.c print.h
	$(CC) -c print.c $(CFLAGS)

tetris_data.o: tetris_data.c
	$(CC) -c tetris_data.c $(CFLAGS)

clean:
	rm -f $(SOBJS) $(TOBJS) $(SOUT) $(TOUT)
