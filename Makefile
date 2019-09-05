# Makefile for building custom block allocator with test file

# For another architecture 
# it's possible to add CROSS_COMPILE variable
CC	:= gcc
LD 	:= gcc
TARGETS	:= tests
CFLAGS	:= -c
OBJECTS	:= tests.o my_alloc.o

all: Makefile $(TARGETS)

tests: my_alloc.o tests.o
	$(LD) -o $@ $^

my_alloc.o: my_alloc.c
	$(CC) $(CFLAGS) my_alloc.c

tests.o: tests.c
	$(CC) $(CFLAGS) tests.c

clean:
	rm -f $(OBJECTS) $(TARGETS)
