#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "../tokenizer/tokens.h"

extern const char* lexErrs[];
void throwError(enum TokenType attribute, int aspect, int start, int length);
int initializeErrorHandler();

Token* getNextErrorToken();

#endif // ERROR_HANDLER_H
