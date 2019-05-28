#########################################################################
# ECE252 Lab Makefile
# Y. Huang, 2018/10/15
#########################################################################

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g

SRCS=cmd_arg.c
OBJS=cmd_arg.o

all: cmd_arg.out

cmd_arg.out: $(OBJS) 
	$(LD) $(LDFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $<

%.d: %.c
	gcc -MM -MF $@ $<  

-include $(SRCS:.c=.d) 

.PHONY: clean
clean:
	rm -f *.d *.o *.out 
