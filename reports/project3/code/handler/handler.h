#ifndef HANDLER_H
#define HANDLER_H

#include<stdbool.h>
#include "../tokenizer/tokens.h"

int initializeHandler(const char* sourcePath, const char* resPath,
                        const char* listingPath, const char* tokenPath,
                        const char* memPath);
bool handleToken(Token* token);
void outputWidth(char* lex, int width);

#endif // HANDLER_H
