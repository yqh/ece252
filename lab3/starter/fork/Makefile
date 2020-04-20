
# Makefile, ECE252  
# Yiqing Huang, 2019/06/12

CC = gcc       # compiler
CFLAGS = -Wall -g  -std=gnu99# compilation flg 
LD = gcc       # linker
LDFLAGS = -g   # debugging symbols in build
LDLIBS =       # link with libz

# For students 
LIB_UTIL = 
SRCS   = forkN.c zombie.c
OBJS1   = forkN.o $(LIB_UTIL) 
OBJS2   = zombie.o $(LIB_UTIL) 

TARGETS= forkN.out zombie.out 

all: ${TARGETS}

forkN.out: $(OBJS1) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

zombie.out: $(OBJS2) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *.d *.o *~ $(TARGETS) 
