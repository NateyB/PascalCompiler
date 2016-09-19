#ifndef PROCESSOR_H_
#define PROCESSOR_H_

enum TokenType {ASSIGNOP, RELOP, IDRES, LONGREAL, REAL, INT, UNREC};

// The token data type (essentially a tuple :: (TokenType, int))
typedef struct T_Type {
    enum TokenType category;
    union {
        int type;
        char* id;
    };

} Token;

Token* getNextToken();
int initializeTokens(FILE* sourceFile, FILE* resFile);

#endif // PROCESSOR_H_
