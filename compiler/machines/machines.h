#ifndef MACHINES_H
#define MACHINES_H

typedef int (*machine)(Token*, char*, int);

int intMachine(Token* storage, char* str, int start);
int realMachine(Token* storage, char* str, int start);
int longRealMachine(Token* storage, char* str, int start);
int grouping(Token* storage, char* str, int start);
int catchall(Token* storage, char* str, int start);
int mulop(Token* storage, char* str, int start);
int addop(Token* storage, char* str, int start);
int whitespace(Token* storage, char* str, int start);
int idres(Token* storage, char* str, int start);
int relop(Token* storage, char* str, int start);


extern const machine machines[];

/* Delete everything below this line and above the endif when complete
enum TokenType {ASSIGNOP, FILEEND, RELOP, ID, CONTROL,
                    ADDOP, MULOP, WS, ARRAY, TYPE, VAR,
                    INT, REAL, PUNC, GROUP, INVERSE, NOOP, LEXERR};

extern const char* catNames[];


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

Token* getNextToken();
int passLine(char* newLine);
int initializeTokens(FILE* resFile);*/

#endif // MACHINES_H
