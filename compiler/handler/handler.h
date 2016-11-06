#ifndef HANDLER_H
#define HANDLER_H

#include<stdbool.h>
#include "../tokenizer/tokens.h"

int initializeHandler(const char* sourcePath, const char* resPath,
                        const char* listingPath, const char* tokenPath);
bool handleToken(Token* token);

#endif // HANDLER_H
