#ifndef TOKENS_H
#define TOKENS_H

#include<stdbool.h>

#include "../dataStructures/linkedList/linkedList.h"

// Must have a boolean indicating whether it is a parameter or not
typedef enum LangType {ERR, REAL, INT, BOOL, PGNAME, PPNAME,
                       PROC, AINT, AREAL} LangType;

enum TokenType {NOOP, FILEEND, ASSIGNOP, RELOP, ID,
                CONTROL, ADDOP, MULOP, WS, ARRAY, TYPE,
                VAR, NUM, PUNC, GROUP, INVERSE,
                LEXERR, SYNERR, SEMERR};

// The token data type
typedef struct T_Type {
    enum TokenType attribute; // Attribute

    union { // Aspect or character pointer
        int aspect;
        char* id;
    };

    int start; // Start in the line
    int length; // Length of the lexeme

    union { // Value of the number, or length of the array
        int int_val;
        double real_val;
        int array_length;
    };

    LangType type; // The type of the token
    bool param; // Whether the token is a parameter or not

} Token;

extern const Token eof_tok;
extern const Token lparen_tok;
extern const Token rparen_tok;
extern const Token plus_tok;
extern const Token comma_tok;
extern const Token minus_tok;
extern const Token semic_tok;
extern const Token colon_tok;
extern const Token period_tok;
extern const Token dotdot_tok;
extern const Token lbrac_tok;
extern const Token rbrac_tok;
extern const Token addop_tok;
extern const Token array_tok;
extern const Token assignop_tok;
extern const Token begin_tok;
extern const Token call_tok;
extern const Token do_tok;
extern const Token else_tok;
extern const Token end_tok;
extern const Token id_tok;
extern const Token if_tok;
extern const Token integer_tok;
extern const Token integer_val_tok;
extern const Token of_tok;
extern const Token real_val_tok;
extern const Token mulop_tok;
extern const Token not_tok;
extern const Token num_tok;
extern const Token procedure_tok;
extern const Token program_tok;
extern const Token real_tok;
extern const Token relop_tok;
extern const Token then_tok;
extern const Token var_tok;
extern const Token while_tok;

extern const char* catNames[19];
extern const char* typeNames[9];
const Token* getTokenFromLex(char* lex);
const char* getLexFromToken(Token* token, bool strict);

// The type; else null if impossible
LangType convert_to_array(LangType type);
LangType convert_from_array(LangType type);

// Returns the type produced by the operation
LangType type_lookup(LangType first, LangType second, Token* op);

// Returns true if the tokens are equivalent, false otherwise
bool tokens_equal(const Token* p1, Token* p2, bool strict);


#endif // TOKENS_H
