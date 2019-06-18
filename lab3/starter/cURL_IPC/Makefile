# Makefile, ECE252  
# Yiqing Huang

CC = gcc 
CFLAGS = -Wall -std=c99 -g # "curl-config --cflags" output is empty  
LD = gcc
LDFLAGS = -std=c99 -g 
LDLIBS = -lcurl -pthread# "curl-config --libs" output 

SRCS   = main.c main_2proc.c main_sem.c
OBJS1  = main.o
OBJS2  = main_2proc.o
TARGETS= main.out main_2proc.out

all: ${TARGETS}

main.out: $(OBJS1) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

main_2proc.out: $(OBJS2) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *~ *.d *.o *~ $(TARGETS) *.png
