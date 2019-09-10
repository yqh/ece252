CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g


OBJS=main_segv.o

all: main_segv.out

main_segv.out: $(OBJS) 
	$(LD) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) 

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.out 
