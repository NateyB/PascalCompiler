objects := $(shell find compiler -name '*.c')
CFLAGS=-Wno-logical-op-parentheses

analyzermake: $(objects)
	gcc $(CFLAGS) -g -o pascompiler $(objects)
