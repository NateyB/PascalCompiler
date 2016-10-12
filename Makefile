objects := $(shell find compiler -name '*.c')

analyzermake: $(objects)
	gcc -g -o compiler.out $(objects)
