#ifndef TOKENS_H
#define TOKENS_H

#include "../dataStructures/linkedList/linkedList.h"

enum TokenType {NOOP, ASSIGNOP, FILEEND, RELOP, ID,
                CONTROL, ADDOP, MULOP, WS, ARRAY, TYPE,
                VAR, INT, REAL, PUNC, GROUP, INVERSE,
                LEXERR, SYNERR};

// The token data type
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

extern const char* catNames[19];

#endif // TOKENS_H
