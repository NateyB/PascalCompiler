objects := $(shell find compiler -name '*.c')
CFLAGS=-Wincompatible-pointer-types-discards-qualifiers

analyzermake: $(objects)
	gcc $(CFLAGS) -g -o pascompiler $(objects)
