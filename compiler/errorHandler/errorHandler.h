#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "../tokenizer/tokens.h"

extern const char* lexErrs[];
void throwError(enum TokenType category, int type, int start, int length);
void initializeErrorHandler();

Token* getNextErrorToken();

#endif // ERROR_HANDLER_H
