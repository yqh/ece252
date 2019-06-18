
# Makefile, ECE252  
# Yiqing Huang, 2019/06/12

CC = gcc       # compiler
CFLAGS = -Wall -g -std=gnu99# compilation flg 
LD = gcc       # linker
LDFLAGS = -g -std=gnu99   # debugging symbols in build
LDLIBS  =-lpthread  # link with libpthread

# For students 
LIB_UTIL = 
SRCS   = sem_simple.c
OBJS3  = sem_simple.o

TARGETS=sem_simple.out

all: ${TARGETS}
sem_simple.out: ${OBJS3}
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *.d *.o *~ $(TARGETS) 
