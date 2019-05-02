
# Makefile, ECE252  
# Yiqing Huang 

CC = gcc
CFLAGS = -Wall -g -std=c99 
LD = gcc
LDFLAGS = -g -std=c99
LDLIBS = -pthread

SRCS   = main.c
OBJS   = main.o
TARGETS= main.out

all: ${TARGETS}

main.out: $(OBJS) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *~ *.d *.o $(TARGETS) 
