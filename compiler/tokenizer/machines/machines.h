#ifndef MACHINES_H
#define MACHINES_H
#include <stdio.h>
#include "../tokens.h"

typedef int (*machine)(Token*, char*, int);

int intMachine(Token* storage, char* str, int start);
int realMachine(Token* storage, char* str, int start);
int longRealMachine(Token* storage, char* str, int start);
int grouping(Token* storage, char* str, int start);
int catchall(Token* storage, char* str, int start);
int mulop(Token* storage, char* str, int start);
int addop(Token* storage, char* str, int start);
int whitespace(Token* storage, char* str, int start);
int relop(Token* storage, char* str, int start);

int idres(Token* storage, char* str, int start);
int initIDResMachine(FILE* resFile);

extern const machine machines[];
#endif // MACHINES_H
