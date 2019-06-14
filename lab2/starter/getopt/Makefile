
# Makefile, ECE252  
# Yiqing Huang 

CC = gcc
CFLAGS = -Wall -g -std=gnu99
LD = gcc
LDFLAGS = -g 
LDLIBS = 

SRCS   = main_getopt.c
OBJS   = main_getopt.o
TARGETS= main_getopt.out

all: ${TARGETS}

main_getopt.out: $(OBJS) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *~ *.d *.o $(TARGETS) 
