
# Makefile, ECE252  
# Yiqing Huang, 2019/06/12

CC = gcc       # compiler
CFLAGS = -Wall -g # compilation flg 
LD = gcc       # linker
LDFLAGS = -g   # debugging symbols in build
LDLIBS =       # link with libz

# For students 
LIB_UTIL = 
SRCS   = shm_stack.c shm_simple.c shm_struct.c
OBJS1  = shm_simple.o $(LIB_UTIL) 
OBJS2  = shm_struct.c shm_stack.o $(LIB_UTIL) 

TARGETS= shm_simple.out shm_struct.out

all: ${TARGETS}

shm_simple.out: $(OBJS1) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

shm_struct.out: $(OBJS2) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *.d *.o *~ $(TARGETS) 
