# ECE252 File System Lab Makefile
# Y. Huang, 2018/10/15

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g


OBJS1=ls_ftype.o
OBJS2=ls_fname.o

all: ls_ftype.out ls_fname.out

ls_ftype.out: $(OBJS1) 
	$(LD) $(LDFLAGS) -o $@ $^

ls_fname.out: $(OBJS2) 
	$(LD) $(LDFLAGS) -o $@ $^ 

.c.o:
	$(CC) $(CFLAGS) -c $<

%.d: %.c
	gcc -MM -MF $@ $<  


.PHONY: clean
clean:
	rm -f *.d *.o *.out 
