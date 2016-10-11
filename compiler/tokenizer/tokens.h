#ifndef TOKENS_H
#define TOKENS_H

#include "../dataStructures/linkedList/linkedList.h"

enum TokenType {NOOP, ASSIGNOP, FILEEND, RELOP, ID,
                CONTROL, ADDOP, MULOP, WS, ARRAY, TYPE,
                VAR, INT, REAL, PUNC, GROUP, INVERSE,
                LEXERR, SYNERR};

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

const char* catNames[] = {"NOOP", "ASSIGNOP", "FILEEND", "RELOP", "ID",
                          "CONTROL", "ADDOP", "MULOP", "WS", "ARRAY", "TYPE",
                          "VAR", "INT", "REAL", "PUNC", "GROUP", "INVERSE",
                          "LEXERR", "SYNERR"};

#endif // TOKENS_H
