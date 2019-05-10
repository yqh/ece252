
# Makefile, ECE252  
# Yiqing Huang, 2018/11/02

CC = gcc
CFLAGS = -Wall -g
LD = gcc
LDFLAGS = -g 
LDLIBS =

SRCS_LIB =
SRCS   = main.c $(SRCS_LIB)
LIBS   =
OBJS   = main.o $(LIBS)
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
