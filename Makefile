objects := $(shell find compiler -name '*.c')
CFLAGS=-w

analyzermake: $(objects)
	gcc $(CFLAGS) -g -o pascompiler $(objects)
