#ifndef TOKENS_H
#define TOKENS_H

#include "../dataStructures/linkedList/linkedList.h"

enum TokenType {NOOP, ASSIGNOP, FILEEND, RELOP, ID,
                CONTROL, ADDOP, MULOP, WS, ARRAY, TYPE,
                VAR, NUM, PUNC, GROUP, INVERSE,
                LEXERR, SYNERR};

// The token data type
typedef struct T_Type {
    enum TokenType attribute; // Attribute
    int start; // Start in the line
    int length; // Length of the lexeme

    union { // Aspect or character pointer
        int aspect;
        char* id;
    };

    union { // Value of the number
        int int_val;
        double real_val;
    };
} Token;

extern const char* catNames[19];

#endif // TOKENS_H
