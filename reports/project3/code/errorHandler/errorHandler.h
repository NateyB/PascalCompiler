#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "../tokenizer/tokens.h"

extern const char* lexErrs[];
char* synErr;
LinkedList* semErrs;

void throw_sem_error(char* msg);
void throw_syn_error(Token* received, const Token** expected, int exp_size);
void throw_lex_error(enum TokenType attribute, int aspect, int start, int length);
int initializeErrorHandler();

Token* getNextErrorToken();

#endif // ERROR_HANDLER_H
