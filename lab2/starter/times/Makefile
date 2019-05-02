
# Makefile, ECE252  
# Yiqing Huang, 2018/11/02

CC = gcc
CFLAGS = -Wall -g # "curl-config --cflags" output is NULL 
LD = gcc
LDFLAGS = -g 
#LDLIBS = -L/usr/lib/x86_64-linux-gnu -lcurl # "curl-config --libs" output 
LDLIBS = #-lcurl -lpng# "curl-config --libs" output 

SRCS_LIB = # util_curl.c util.c
SRCS   = main.c $(SRCS_LIB)
LIBS   = # util_curl.o util.o
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
	rm -f *.d *.o $(TARGETS) 
