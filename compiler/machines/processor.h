#ifndef PROCESSOR_H_
#define PROCESSOR_H_

enum TokenType {ASSIGNOP, FILEEND, RELOP, IDRES,
                    ADDOP, MULOP, WS, ARRAYINIT, TYPE,
                    INT, REAL, PUNCTUATION, GROUPING, UNREC};


// The token data type (essentially a tuple :: (TokenType, int/id))
typedef struct T_Type {
    enum TokenType category;
    union {
        int type;
        double val;
        char* id;
    };
} Token;

Token* getNextToken();
int initializeTokens(FILE* sourceFile, FILE* resFile);

#endif // PROCESSOR_H_
