#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include<stdio.h>

#include "../dataStructures/linkedList/linkedList.h"

enum TokenType {ASSIGNOP, FILEEND, RELOP, ID, CONTROL,
                    ADDOP, MULOP, WS, ARRAY, TYPE, VAR,
                    INT, REAL, PUNC, GROUP, INVERSE, NOOP, LEXERR};

// TODO The reserved words initialization needs to be separated out somehow.
extern const char* catNames[];
extern char** reservedWords;
extern int numReserved;
extern enum TokenType* categories;
extern int* attributes;

LinkedList* symbolTable;

static LinkedList* errorList;
static struct node* errorHead;


// The token data type (essentially a tuple :: (TokenType, int/id))
typedef struct T_Type {
    enum TokenType category;
    int start;
    int length;
    union {
        int type;
        double val;
        char* id;
    };
} Token;

void throwError(enum TokenType category, int type, int start, int length);
int getIndex(const char** array, size_t arr_size, char* item);
Token* getNextToken();
int passLine(char* newLine);
int initializeTokens(FILE* resFile);

#endif // PROCESSOR_H_
