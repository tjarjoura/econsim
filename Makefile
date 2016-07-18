SRCS:= error.c main.c render.c util.c world.c
LDFLAGS:= -lm -lfann -lSDL2
CFLAGS:= -Wall -g
PROGNAME:= econsim

all:
	gcc -o $(PROGNAME) $(CFLAGS) $(SRCS) $(LDFLAGS)

