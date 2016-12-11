objects := $(shell find compiler -name '*.c')
CFLAGS=

analyzermake: $(objects)
	gcc $(CFLAGS) -g -o pascompiler $(objects)
