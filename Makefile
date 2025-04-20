# Compiler and flags
CC      = gcc
CFLAGS  = -std=c99 -g -Wall -fsanitize=address,undefined

# Default recipe when you type "make" with no arguments
all: memgrind

# Build memgrind from .o files
memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind

# Build memgrind.o from memgrind.c
# Note: we include mymalloc.h so macros for malloc/free apply.
memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

# Build mymalloc.o from mymalloc.c
mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

# Optional: a 'test' target to run memgrind if you want
test: memgrind
	./memgrind

# Clean up
clean:
	rm -f *.o memgrind