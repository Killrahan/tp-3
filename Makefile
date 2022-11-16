SRCS = main.c BTree.c dict.c token.c simplifytree.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = main


CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG)
runwin: $(PROG)
	$(PROG).exe

BTree.o: BTree.h
main.o: BTree.h dict.h token.h simplifytree.h
dict.o: dict.h
token.o: token.h
simplifytree.o: simplifytree.h BTree.h dict.h token.h


