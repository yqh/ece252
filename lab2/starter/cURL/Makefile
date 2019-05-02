# Makefile, ECE252  
# Yiqing Huang, 2018/11/02

CC = gcc 
CFLAGS = -Wall -std=c99 -g # "curl-config --cflags" output is empty  
LD = gcc
LDFLAGS = -std=c99 -g 
LDLIBS = -lcurl # "curl-config --libs" output 

SRCS   = main_simple.c main_write_callback.c main_write_header_cb.c
OBJS1  = main_simple.o
OBJS2  = main_write_callback.o
OBJS3  = main_write_header_cb.o
TARGETS= main_simple.out main_write_callback.out main_write_header_cb.out

all: ${TARGETS}

main_simple.out: $(OBJS1) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

main_write_callback.out: $(OBJS2) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

main_write_header_cb.out: $(OBJS3) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *~ *.d *.o $(TARGETS) *.png
